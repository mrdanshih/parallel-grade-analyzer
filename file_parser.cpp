#include "file_parser.h"

std::vector<Student> parseFileIntoStudentArray(const std::string& filename) {
	std::ifstream file;
	file.open(filename);
	
	std::vector<Student> students;
	std::string line;

	// Skip header line
	std::getline(file, line);

	// Get data lines
	while(std::getline(file, line)) {
		unsigned int commaIndex = line.find(",");
		quint64 studentID = std::stol(line.substr(0, commaIndex));
		float grade = std::stof(line.substr(commaIndex + 1));
	}

	return students;
}