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

	std::vector<std::vector<std::string>> process_assignments = create_processes(num_processes, class_name);



	int status;
	pid_t waiting_pid;
	// try to wait for any children while there exists at least one
	while ((waiting_pid = wait(&status)) > 0);
}

std::vector<std::vector<std::string>> create_processes(int num_processes, std::vector<std::string> class_names) {
	std::vector<std::vector<std::string>> process_file_assignments{std::min((size_t) num_processes, class_names.size())};
	std::cout << process_file_assignments.size() << std::endl;
	int x = 0;
	for (int i = 0; i < num_processes; i++) {
	    switch(fork()) {
	    	case 0: /* child */
	    		printf("Child process is created. (pid: %d)\n", getpid());
	    		x += i;
	    		sleep(num_processes - i);
	    		printf("Child process is terminated. (pid: %d)\n", getpid());
	    		printf("CHILD X = %d\n", x);
	    		exit(0);

	    	case -1:
	    		printf("FAILURE\n");
	    		break;
	    }
	}

	return process_file_assignments;

}
