#ifndef _FILE_PARSER
#define _FILE_PARSER

#include <fstream>
#include <vector>
#include <iostream>
#include "Student.h"

std::vector<Student> parseFileIntoStudentVector(const std::string& filename);



#endif