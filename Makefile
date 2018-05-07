EXEC=grade_analyzer

CC=g++
CFLAGS=-std=c++11 -I.


%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

${EXEC}: main.o multithreading.o file_handler.o GradeProcessor.o
	g++ -o ${EXEC} main.o multithreading.o file_handler.o GradeProcessor.o -I. -lpthread 


clean:
	rm -rf ./${EXEC}
	rm -rf ./*.o
