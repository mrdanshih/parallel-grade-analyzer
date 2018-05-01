#ifndef __STUDENT
#define __STUDENT

typedef unsigned long long quint64;

struct Student {
	quint64 id;
	float grade;
};

struct ClassInfo {
	std::string className;
	std::vector<Student> students;
	quint64 score_sum;
	float average;
	float median;
	float stdDev;
};


#endif