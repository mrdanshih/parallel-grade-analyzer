# parallel-grade-analyzer
A command-line C++ program that processes large input files containing students' grades in classes using multiprocessing and multithreading for concurrency and parallelism.

Usage: `grade_analyzer <# of processes> <# of threads>`

Program is executed via command line, taking arguments for max # of processes and # of threads to spawn.

The program then does the following:
* Creates up to the max # of processes for parsing input CSV files (specified in the program's main function). It there are processes than files, each process is assigned a file. Each process:
   * Reads and parses its assigned input CSV file(s).
   * Each process creates the specified number of threads that perform a multi-threaded merge sort add up the sum of grades (for stat calculation). 
   * Once multi-threading proecssing is complete, mean, median, and standard deviation statistics are computed.
   * Each proecss writes output files containing the sorted class grades and statistics, to an "output" folder (which must exist in the executing program's working directory).
