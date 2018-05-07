#ifndef _FILE_PARSER
#define _FILE_PARSER

#include <fstream>
#include <vector>
#include <iostream>
#include "Student.h"

ClassInfo parseFileIntoClassInfo(const std::string& filename);

void writeFilesFromClassInfo(ClassInfo& classInfo);

#endif