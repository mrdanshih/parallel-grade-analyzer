#ifndef __STUDENT
#define __STUDENT

#include <vector>

typedef unsigned long long quint64;

struct Student {
	quint64 id;
	double grade;
};

struct ClassInfo {
	std::string classFilePath;
	std::vector<Student> students;
	double score_sum;
	float average;
	float median;
	float stdDev;
};



#endif