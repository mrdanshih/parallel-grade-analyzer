#ifndef __P1_THREADS
#define __P1_THREADS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <utility>
#include <pthread.h>

#include "p1_process.h"
#include "Student.h"

// This header/source file handles the computations done by a single thread:
// - sorting the list of students using mergesort
// - computing the sum of student scores.

struct ClassInfo;

struct SortThreadData {
	int thread_no;

	std::vector<Student>& students;
	double thread_sum; 	// This thread's sum of scores.

	int array_low;	// Lowest index of list range that this thread is responsible for.
	int array_hi;	// Highest index of list range that this thread is responsible for.
};

struct MergeThreadData {
	std::vector<Student>& students;

	int a_start;
	int a_end;
	int b_start;
	int b_end;
};

void perform_threaded_computations(ClassInfo& classInfo, unsigned int num_threads);
void merge_thread_sorted_sections(std::vector<SortThreadData>& sortThreadArgs, std::vector<Student>& students);
std::vector<MergeThreadData> generateInitialMergeThreadArgs(std::vector<SortThreadData>& sortThreadArgs, std::vector<Student>& students);

void* sort_thread_fn(void* arg);
void* merge_thread_fn(void* arg);


void merge_sort(int lo, int hi, std::vector<Student>& students);
void merge(int a_start, int a_end, int b_start, int b_end, std::vector<Student>& students);

#endif
