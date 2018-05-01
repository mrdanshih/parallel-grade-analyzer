#ifndef __P1_THREADS
#define __P1_THREADS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>

#include "p1_process.h"

struct Student;

void merge_sort(int lo, int hi, Student students[], unsigned int len);

#endif
