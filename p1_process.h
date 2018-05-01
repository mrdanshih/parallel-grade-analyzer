#ifndef __P1_PROCESS
#define __P1_PROCESS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <algorithm>

#include "p1_threads.h"
#include "file_parser.h"
#include "Student.h"
#include "ProcessHandler.h"

void get_statistics(std::vector<std::string> class_names, int num_processes, int num_threads);

// Creates an array of processes, up to the maximum number of processes (minimum of # processes + file names.)
// Each process has a list of filenames to process. 
std::vector<std::vector<std::string>> create_processes(int num_processes, std::vector<std::string>& class_names);

// Runs process.
void run_processes(std::vector<std::vector<std::string>>& process_assignments);

// Execute an individual process.
void execute_process(std::vector<std::string>& file_assignments);

#endif
