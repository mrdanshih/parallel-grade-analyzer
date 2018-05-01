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

std::vector<std::vector<Student>> ProcessHandler::run_processes() {
	all_sorted_students.clear();

	int x = 0;
	for (int i = 0; i < process_file_assignments.size(); ++i) {
	    switch(fork()) {
	    	case 0: /* child */
	    		// EXECUTE process  with given file list.
	    		
	    		printf("Child process is created, has %d files. (pid: %d)\n", (int) process_file_assignments.at(i).size(), getpid());
	    		x += i;
	    		execute_single_process(process_file_assignments.at(i));

	    		sleep(process_file_assignments.size() - i);
	    		printf("Child process is terminated. (pid: %d)\n", getpid());
	    		printf("CHILD X = %d\n", x);
	    		exit(0);

	    	case -1:
	    		printf("FAILURE\n");
	    		break;
	    }
	}

	int status;
	pid_t waiting_pid;
	// try to wait for any children while there exists at least one
	while ((waiting_pid = wait(&status)) > 0);

	return all_sorted_students;


}

void ProcessHandler::execute_single_process(std::vector<std::string>& files) {
	for(std::string& file: files) {
		std::vector<Student> unsorted_students = parseFileIntoStudentVector(file);
		// Partition list and make threads that do the parallel sorting
		int partition_length = std::ceil((float) unsorted_students.size() / num_threads);

		for(int thread_no = 0; thread_no < num_threads; ++thread_no) {
			if(thread_no == num_threads - 1) {	// Last thread may have a little more.
				printf("%d - %d\n", thread_no * partition_length, std::min((int)unsorted_students.size(), (thread_no + 1) * partition_length));
			} else {
				printf("%d - %d\n", thread_no * partition_length, (thread_no + 1) * partition_length);
			}
			
		}

	}

}




