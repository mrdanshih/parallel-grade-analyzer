#include "file_parser.h"

ClassInfo parseFileIntoClassInfo(const std::string& filename) {
	std::ifstream file;
	file.open(filename);

	if(file.fail()) {
		throw std::exception();
	}
	
	ClassInfo classInfo;
	classInfo.className = filename;	// Change to actual  className from filename.
	classInfo.score_sum = 0;
	classInfo.average = 0;
	
	std::string line;

	// Skip header line
	std::getline(file, line);

	// Get data lines
	while(std::getline(file, line)) {
		unsigned int commaIndex = line.find(",");
		quint64 studentID = std::stol(line.substr(0, commaIndex));
		float grade = std::stof(line.substr(commaIndex + 1));

		classInfo.students.push_back(Student{studentID, grade});
	}

	return classInfo;
}