#include "GradeProcessor.h"
#include <iomanip>

GradeProcessor::GradeProcessor(std::vector<std::string>& file_names, int max_num_processes, int max_num_threads)
	: num_threads{max_num_threads}, process_file_assignments{std::min((size_t) max_num_processes, file_names.size())}
{
	create_processes(file_names);
}

void GradeProcessor::create_processes(std::vector<std::string>& file_names) {
	for(int i = 0; i < file_names.size(); ++i) {
		process_file_assignments.at(i % process_file_assignments.size()).push_back(file_names.at(i));
	}
}

std::vector<ClassInfo> GradeProcessor::run_processes() {
	all_sorted_classes.clear();

	for (int i = 0; i < process_file_assignments.size(); ++i) {
	    switch(fork()) {
	    	case 0: /* child */
	    		// EXECUTE process  with given file list.
	    		printf("Child process is created, has %d files. (pid: %d)\n", (int) process_file_assignments.at(i).size(), getpid());
	    		execute_single_process(process_file_assignments.at(i));
	    		printf("Child process is terminated. (pid: %d)\n", getpid());
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

	return all_sorted_classes;


}

void GradeProcessor::execute_single_process(std::vector<std::string>& files) {
	for(std::string& file: files) {
		ClassInfo classInfo = parseFileIntoClassInfo(file);
		size_t unsorted_students_size = classInfo.students.size();
		perform_threaded_computations(classInfo, (unsigned int) std::min((int) unsorted_students_size, num_threads));
		
		// for(Student& student: classInfo.students) {
		// 	std::cout << std::fixed << std::setprecision(10) << student.grade << std::endl;
		// }

		calculate_stats(classInfo);
		writeFilesFromClassInfo(classInfo);
	}
}

void GradeProcessor::calculate_stats(ClassInfo& classInfo) {
	std::vector<Student>& students = classInfo.students;
	// Mean.
	classInfo.average = classInfo.score_sum / students.size();
	// Median.
	int mid = students.size() / 2;
	if(students.size() % 2 == 0) {
		classInfo.median = (students.at(mid).grade + students.at(mid + 1).grade) / 2;
	} else {
		classInfo.median = students.at(mid).grade;
	}

	// Standard dev.
	double sq_diff_sum = 0;
	for(Student& student: students) {
		sq_diff_sum += std::pow(student.grade - classInfo.average, 2);
	}

	classInfo.stdDev = std::sqrt(sq_diff_sum / students.size());
}




