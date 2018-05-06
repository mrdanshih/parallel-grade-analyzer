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

	std::vector<ThreadData> threadArgs;

	for(int thread_no = 0; thread_no < num_threads; ++thread_no) {
		// Determine the lo & hi indices of this thread's partiion of the array.
		int lo = thread_no * partition_length;
		int hi = std::min((int) unsorted_students_size - 1, (thread_no + 1) * partition_length);
		printf("%d-%d.\n", lo, hi);
		threadArgs.push_back(ThreadData{thread_no, classInfo, 0, lo, hi});
	}

	std::vector<pthread_t> threads{num_threads};


	for(int thread_no = 0; thread_no < num_threads; ++thread_no) {
		pthread_create(&threads[thread_no], NULL, thread_fn, &threadArgs[thread_no]);
	}


	// Block till all threads complete;
	for(int thread_no = 0; thread_no < num_threads; ++thread_no) {
		pthread_join(threads[thread_no], NULL);
	}


	for(int thread_no = 0; thread_no < num_threads; ++thread_no) {
		classInfo.score_sum += threadArgs[thread_no].thread_sum;
	}

	printf("MULTI-THREADED: %f\n", classInfo.score_sum);}


void* thread_fn(void* arg) {
	ThreadData* tData = (ThreadData*) arg;
	ClassInfo& classInfo = tData->classInfo;

	for(int i = tData->array_low; i <= tData->array_hi; ++i) {
		tData->thread_sum += classInfo.students.at(i).grade;
	}

	merge_sort(tData->array_low, tData->array_hi, classInfo.students);

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
		if(students.at(a).grade < students.at(b).grade) {
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