#include "file_parser.h"
#include <iomanip>

std::string extractFileName(const std::string& str) {
	// From https://stackoverflow.com/questions/14143801/return-filename-from-path
	size_t found = str.find_last_of("/\\");
    std::string path = str.substr(found+1);

    return path.substr(0, path.find_last_of("."));
}


ClassInfo parseFileIntoClassInfo(const std::string& filename) {
	std::ifstream file;
	file.open(filename);

	if(file.fail()) {
		throw std::exception();
	}
	
	ClassInfo classInfo;
	classInfo.classFilePath = filename;
	classInfo.score_sum = 0;
	classInfo.average = 0;

	std::string line;

	// Skip header line
	std::getline(file, line);

	// Get data lines
	while(std::getline(file, line)) {
		unsigned int commaIndex = line.find(",");
		quint64 studentID = std::stol(line.substr(0, commaIndex));
		double grade = std::stod(line.substr(commaIndex + 1));
		classInfo.students.push_back(Student{studentID, grade});
	}

	return classInfo;
}

void writeFilesFromClassInfo(ClassInfo& classInfo) {
	std::ofstream file_stats{"./output/" + extractFileName(classInfo.classFilePath) + "-stats.csv"};
	std::ofstream file_sorted{"./output/" + extractFileName(classInfo.classFilePath) + "-sorted.csv"};

	if(file_stats.fail() || file_sorted.fail()) {
		throw std::exception();
	}

	// Stats
	file_stats << "Average,Median,Std. Dev\n";
	file_stats << std::fixed << std::setprecision(3) << classInfo.average << "," << classInfo.median << "," << classInfo.stdDev << "\n";
	file_stats.close();

	// Sorted students
	file_sorted << "Rank,Student ID,Grade\n";

	std::vector<Student>& students = classInfo.students;

	int rank = 1;

	for(Student& student: classInfo.students) {
		file_sorted << rank << ',' << student.id << ',';
		file_sorted << std::setprecision(10) << std::fixed << student.grade << '\n';
		rank++;
	}

	file_sorted.close();






}