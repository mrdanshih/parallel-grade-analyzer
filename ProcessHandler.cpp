#include "ProcessHandler.h"

ProcessHandler::ProcessHandler(std::vector<std::string>& file_names, int max_num_processes, int max_num_threads)
	: num_threads{max_num_threads}, process_file_assignments{std::min((size_t) max_num_processes, file_names.size())}
{
	create_processes(file_names);
}

void ProcessHandler::create_processes(std::vector<std::string>& file_names) {
	for(int i = 0; i < file_names.size(); ++i) {
		process_file_assignments.at(i % process_file_assignments.size()).push_back(file_names.at(i));
	}
}

void ProcessHandler::run_processes() {
	int x = 0;
	for (int i = 0; i < process_file_assignments.size(); ++i) {
	    switch(fork()) {
	    	case 0: /* child */
	    		// EXECUTE process  with given file list.
	    		printf("Child process is created, has %d files. (pid: %d)\n", (int) process_file_assignments.at(i).size(), getpid());
	    		x += i;
	    		sleep(process_file_assignments.size() - i);
	    		printf("Child process is terminated. (pid: %d)\n", getpid());
	    		printf("CHILD X = %d\n", x);
	    		exit(0);

	    	case -1:
	    		printf("FAILURE\n");
	    		break;
	    }
	}
}
