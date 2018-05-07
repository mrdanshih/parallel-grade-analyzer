#ifndef __GRADE_ANALYZER
#define __GRADE_ANALYZER

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

#include "multithreading.h"
#include "file_handler.h"
#include "Student.h"

// GradeProcessor class?
// 	Initializes and runs processes.
class GradeProcessor
{
public:
	GradeProcessor(std::vector<std::string>& file_names, int max_num_processes, int max_num_threads);
	
	// Return vector of ClassInfo, with sorted students in each class, and sum of student scores.
	std::vector<ClassInfo> run_processes();

private:
	int num_threads;
	std::vector<std::vector<std::string>> process_file_assignments;

	std::vector<ClassInfo> all_sorted_classes;

	void create_processes(std::vector<std::string>& file_names);
	void execute_single_process(std::vector<std::string>& files);

	// Calculate average, median, std. dev and populate that info in ClassInfo.
	void calculate_stats(ClassInfo& classInfo);
};

#endif