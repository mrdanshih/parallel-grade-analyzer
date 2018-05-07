#include "p1_process.h"


void get_statistics(std::vector<std::string>& class_name, int num_processes, int num_threads) {

	// You need to create multiple processes here (each process
	// handles at least one file.)

	// Each process should use the sort function which you have defined  		
	// in the p1_threads.cpp for multithread sorting of the data. 
	
	// Your code should be able to get the statistics and generate
	// the required outputs for any number of child processes and threads.
	//parseFileIntoStudentArray("./input/" + class_name[0] + ".csv");


	ProcessHandler handler{class_name, num_processes, num_threads};
	
	// Run processes - sorts students by grades, and calculate stats.
	std::vector<ClassInfo> processed_classes = handler.run_processes();

	// Calculate stats - get a list of ClassStats.

	// Write to files.


	
}



