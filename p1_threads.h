#ifndef __P1_THREADS
#define __P1_THREADS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>

#include "p1_process.h"

// This header/source file handles the computations done by a single thread:
// - sorting the list of students using mergesort
// - computing the sum of student scores.

struct ClassInfo;

struct ThreadData {
	int thread_no;

	ClassInfo& classInfo;

	int array_low;	// Lowest index of list range that this thread is responsible for.
	int array_hi;	// Highest index of list range that this thread is responsible for.
};

void perform_threaded_computations(ClassInfo& classInfo, unsigned int num_threads);

void* thread_fn(void* arg);

void merge_sort(int lo, int hi, ClassInfo ClassInfo, unsigned int len);

#endif
