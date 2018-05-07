#include "p1_threads.h"

// This file includes functions that actually perform the
// computation. You can create a thread with these function
// or directly call this function

void perform_threaded_computations(ClassInfo& classInfo, unsigned int num_threads) {
	size_t unsorted_students_size = classInfo.students.size();
	std::vector<Student>& unsorted_students = classInfo.students;
	// Partition list and make threads that do the parallel sorting (and sum computation)
	int partition_length = std::ceil((float) unsorted_students_size / num_threads);

	// Probably want to get Thread info structs to track what section of list thread shoudl handle.
	// SORTING STRATEGY:
	// -> Each thread x will merge sort its section (N threads, N sections)
	// -> Merge all sections together.
	//		-> min of each array... build up result.

	std::vector<SortThreadData> threadArgs;

	for(int thread_no = 0; thread_no < num_threads; ++thread_no) {
		// Determine the lo & hi indices of this thread's partiion of the array.
		int lo = thread_no * partition_length;
		int hi = std::min((int) unsorted_students_size, (thread_no + 1) * partition_length) - 1;
		// printf("%d - %d\n", lo, hi);
		threadArgs.push_back(SortThreadData{thread_no, classInfo.students, 0, lo, hi});
	}

	std::vector<pthread_t> threads{num_threads};

	// Create threads that do the merge sorting.
	for(int thread_no = 0; thread_no < num_threads; ++thread_no) {
		pthread_create(&threads[thread_no], NULL, sort_thread_fn, &threadArgs[thread_no]);
	}


	// Block till all threads complete;
	for(int thread_no = 0; thread_no < num_threads; ++thread_no) {
		pthread_join(threads[thread_no], NULL);
	}


	for(int thread_no = 0; thread_no < num_threads; ++thread_no) {
		classInfo.score_sum += threadArgs[thread_no].thread_sum;
	}

	// merge sorted sections done by each thread

	// printf("MULTI-THREADED: %f\n", classInfo.score_sum);
	merge_thread_sorted_sections(threadArgs, classInfo.students);
}

void merge_thread_sorted_sections(std::vector<SortThreadData>& sortThreadArgs, std::vector<Student>& students) {
	// Based on algorithm described here: https://courses.engr.illinois.edu/cs241/fa2012/assignments/mergesort/
	std::vector<MergeThreadData> mergeThreadArgs{std::move(generateInitialMergeThreadArgs(sortThreadArgs, students))};
	std::vector<MergeThreadData> currentMergeThreadArgs;

	MergeThreadData* oddOneOutSection = nullptr;

	while(mergeThreadArgs.size() > 1 || oddOneOutSection != nullptr) {
		// printf("SIZE IS: %lu\n", mergeThreadArgs.size());
		if(mergeThreadArgs.size() % 2 == 1 && oddOneOutSection != nullptr) {
			mergeThreadArgs.push_back(*oddOneOutSection);
			// std::cout << "ADDING BACK IN THE ODD ONE OUT" << std::endl;
			oddOneOutSection = nullptr;

		}

		for(int i = 0; i < mergeThreadArgs.size(); i+= 2) {
		// Delegate adjacent sections to merge to the threads.
			if(i == mergeThreadArgs.size() - 1) {
				oddOneOutSection = &mergeThreadArgs.at(i);
				// printf("ODD ONE OUT: %d - %d\n", mergeThreadArgs.at(i).a_start, mergeThreadArgs.at(i).b_end);

			} else {
				int a_start =  mergeThreadArgs.at(i).a_start;
				int a_end =  mergeThreadArgs.at(i).b_end;
				int b_start =  mergeThreadArgs.at(i + 1).a_start;
				int b_end =  mergeThreadArgs.at(i + 1).b_end;
				// printf("Merge: %d - %d  AND %d - %d\n", a_start, a_end, b_start, b_end);
				currentMergeThreadArgs.push_back(MergeThreadData{students, a_start, a_end, b_start, b_end});
			}
		}

		// Start & join threads for this round of threaded merging.
		std::vector<pthread_t> merge_threads{currentMergeThreadArgs.size()};

		for(int thread_no = 0; thread_no < currentMergeThreadArgs.size(); ++thread_no) {
			pthread_create(&merge_threads[thread_no], NULL, merge_thread_fn, &currentMergeThreadArgs[thread_no]);
		}

		// Block till all threads complete;
		for(int thread_no = 0; thread_no < currentMergeThreadArgs.size(); ++thread_no) {
			pthread_join(merge_threads[thread_no], NULL);
		}

		// Update section data for next round of threaded merging
		mergeThreadArgs = std::move(currentMergeThreadArgs);
		currentMergeThreadArgs.clear();
	}

	// std::cout << "DONE! " << std::endl;
	
}

std::vector<MergeThreadData> generateInitialMergeThreadArgs(std::vector<SortThreadData>& sortThreadArgs, std::vector<Student>& students) {
	std::vector<MergeThreadData> mergeThreadArgs;

	for(int i = 0; i < sortThreadArgs.size(); ++i) {
		// "Convert" sortthreaddata to mergethreaddata struct style (so initially, N sorted sections gives N "remaining" merge section)
		int a_start = sortThreadArgs.at(i).array_low;
		int a_end = -1;
		int b_start = -1;
		int b_end = sortThreadArgs.at(i).array_hi;

		mergeThreadArgs.push_back(MergeThreadData{students, a_start, a_end, b_start, b_end});
	}

	return mergeThreadArgs;
}

void* sort_thread_fn(void* arg) {
	SortThreadData* tData = (SortThreadData*) arg;
	std::vector<Student>& students = tData->students;

	for(int i = tData->array_low; i <= tData->array_hi; ++i) {
		tData->thread_sum += students.at(i).grade;
	}

	merge_sort(tData->array_low, tData->array_hi, students);

	pthread_exit(0);
}

void* merge_thread_fn(void* arg) {
	MergeThreadData* tData = (MergeThreadData*) arg;
	// std::cout << "START MERGE" << std::endl;
	merge(tData->a_start, tData->a_end, tData->b_start, tData->b_end, tData->students);
	pthread_exit(0);
}

void merge_sort(int lo, int hi, std::vector<Student>& students) {
	// recursive merge sort, O(N log N)
	
	// if size 1, return.

	// else...
	// split into two halves.
	// merge_sort(left), merge_sort(right)
	// merge.
	if(hi - lo + 1 <= 1) {
		return;
	}

	int mid = lo + (hi - lo) / 2;
	merge_sort(lo, mid, students);
	merge_sort(mid + 1, hi, students);
	merge(lo, mid, mid + 1, hi, students);
}

void merge(int a_start, int a_end, int b_start, int b_end, std::vector<Student>& students) {

	// Merge two sections of vector together.
	// O(N) time, O(N) space.
	std::vector<Student> merged_students;

	int a = a_start;
	int b = b_start;

	// While both sections have elements to merge...
	while(a <= a_end && b <= b_end) {
		if(students.at(a).grade > students.at(b).grade) {
			merged_students.push_back(students.at(a));
			++a;
		} else {
			merged_students.push_back(students.at(b));
			++b;
		}
	}

	// Merge remaining from section A
	for(; a <= a_end; ++a) {
		merged_students.push_back(students.at(a));
	}
	
	// Merge remaining from section B
	for(; b <= b_end; ++b) {
		merged_students.push_back(students.at(b));
	}

	// Copy back to original list
	int merged_index = 0;
	for(; a_start <= b_end; ++a_start) {
		// using move to avoid extra copy
		students.at(a_start) = std::move(merged_students.at(merged_index));
		++merged_index;
	}
}