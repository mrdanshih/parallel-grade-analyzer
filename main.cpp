#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <pthread.h>

#include "GradeProcessor.h"
#include "Student.h"

void get_statistics(std::vector<std::string>& class_name, int num_processes, int num_threads) {

	GradeProcessor processor{class_name, num_processes, num_threads};
	// Run processes - sorts students by grades, and calculate stats.
	std::vector<ClassInfo> processed_classes = processor.run_processes();	
}


int main(int argc, char** argv)
{	
	printf("Main process is created. (pid: %d)\n", getpid());
	int num_processes = 0;
	int num_threads = 0;

	// Input file paths. Progarm will open files from paths given here, and save 
	// output files in "output" folder of whatever root directory it is run from.
	std::vector<std::string> class_name{"./input/os.csv", "./input/architecture.csv", "./input/java.csv", "./input/algorithm.csv", "./input/digital-design.csv"};

	// Check the argument and print error message if the argument is wrong
	if(argc == 3 && (atoi(argv[1]) > 0 && atoi(argv[2]) > 0))
	{
		num_processes = atoi(argv[1]);
		num_threads = atoi(argv[2]);
		// Call the process
		// For bench marking.
		auto start = std::chrono::high_resolution_clock::now();
		get_statistics(class_name, num_processes, num_threads);
		auto end = std::chrono::high_resolution_clock::now();
		printf("All grade analysis completed in %f seconds.\n", std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() / (double) 1000);
	}
	else
	{
		printf("[ERROR] Expecting 2 arguments with integral value greater than zero.\n");
		printf("[USAGE] grade_analyzer <number of processes> <number of threads>\n");
	}
	printf("Main process is terminated. (pid: %d)\n", getpid());
	return 0;
	
}








