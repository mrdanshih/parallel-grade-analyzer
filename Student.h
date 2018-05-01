#ifndef __STUDENT
#define __STUDENT

typedef unsigned long long quint64;

struct Student {
	quint64 id;
	float grade;
};

struct ClassStats {
	std::string className;
	float average;
	float median;
	float stdDev;
};


#endif