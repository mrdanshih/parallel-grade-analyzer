#ifndef __PROCESS_HANDLER
#define __PROCESS_HANDLER

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <pthread.h>
#include <unistd.h>
#include <algorithm>

#include "p1_threads.h"
#include "file_parser.h"
#include "Student.h"

// ProcessHandler class?
// 	Initializes and runs processes.
class ProcessHandler
{
public:
	ProcessHandler(std::vector<std::string>& file_names, int max_num_processes, int max_num_threads);
	std::vector<std::vector<Student>> run_processes();

private:
	int num_threads;
	std::vector<std::vector<std::string>> process_file_assignments;

	std::vector<std::vector<Student>> all_sorted_students;

	void create_processes(std::vector<std::string>& file_names);
	void execute_single_process(std::vector<std::string>& files);
};

#endif