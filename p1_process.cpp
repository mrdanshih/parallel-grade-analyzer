#include "p1_process.h"


void get_statistics(std::vector<std::string> class_name, int num_processes, int num_threads) {

	// You need to create multiple processes here (each process
	// handles at least one file.)

	// Each process should use the sort function which you have defined  		
	// in the p1_threads.cpp for multithread sorting of the data. 
	
	// Your code should be able to get the statistics and generate
	// the required outputs for any number of child processes and threads.
	//parseFileIntoStudentArray("./input/" + class_name[0] + ".csv");

	/*
		1. Create processes. Assign file to processes in sequential order. If num_processes < num_files, 
			then delegate assign multiple files to the processes (round robin fashion)
			
			Each process should be aware of how many files its dealt (encapsulate? an array of file vectors?)

		2. Each process should process the file it receives by parsing it into Students vector.

	*/

	ProcessHandler handler{class_name, num_processes, num_threads};
	std::vector<std::vector<Student>> sorted_classes = handler.run_processes();

	// Calculate stats - get a list of ClassStats.

	// Write to files.


	int status;
	pid_t waiting_pid;
	// try to wait for any children while there exists at least one
	while ((waiting_pid = wait(&status)) > 0);
}

