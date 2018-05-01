EXEC=p1_exec

CC=g++
CFLAGS=-std=c++11 -I.


%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

${EXEC}: main.o p1_process.o p1_threads.o file_parser.o ProcessHandler.o
	g++ -o ${EXEC} main.o p1_process.o p1_threads.o file_parser.o ProcessHandler.o -I. -lpthread 


clean:
	rm -rf ./${EXEC}
	rm -rf ./*.o
