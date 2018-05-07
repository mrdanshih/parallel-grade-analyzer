#ifndef _FILE_HANDLER
#define _FILE_HANDLER

#include <fstream>
#include <vector>
#include <iostream>
#include "Student.h"

ClassInfo parseFileIntoClassInfo(const std::string& filename);

void writeFilesFromClassInfo(ClassInfo& classInfo);

#endif