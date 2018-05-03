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

		int lo = thread_no * partition_length;
		int hi = std::min((int) unsorted_students_size, (thread_no + 1) * partition_length);
		threadArgs.push_back(ThreadData{thread_no, classInfo, lo, hi});
	}

	std::vector<pthread_t> threads{num_threads};

	for(int thread_no = 0; thread_no < num_threads; ++thread_no) {
		pthread_create(&threads[thread_no], NULL, thread_fn, &threadArgs[thread_no]);
	}

	// Block till all threads complete;
	for(int thread_no = 0; thread_no < num_threads; ++thread_no) {
		pthread_join(threads[thread_no], NULL);
	}

	// for(int thread_no = 0; thread_no < num_threads; ++thread_no) {
	// 	printf("%d - %d\n", threadArgs[thread_no].array_low, threadArgs[thread_no].array_hi);
	// }

	std::cout << " EXIT THIS FUNCTION!" << std::endl;
}

void* thread_fn(void* arg) {
	ThreadData* tData = (ThreadData*) arg;
	ClassInfo classInfo = tData->classInfo;
	for(int i = tData->array_low; i < tData->array_hi; ++i) {
		classInfo.score_sum += classInfo.students.at(i).grade;
	}
	tData->array_low = -150 + tData->thread_no;
	tData->array_hi = 999 + + tData->thread_no;
	pthread_exit(0);
}