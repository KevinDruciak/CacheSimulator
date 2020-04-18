CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

csim: functions.o simulator.o cache.o main.o variables.o
	$(CC) functions.o simulator.o cache.o main.o variables.o -o csim

functions.o: functions.cpp functions.h variables.h
	$(CC) $(CFLAGS) -c functions.cpp

simulator.o: simulator.cpp simulator.h variables.h cache.h
	$(CC) $(CFLAGS) -c simulator.cpp

cache.o: cache.cpp cache.h
	$(CC) $(CFLAGS) -c cache.cpp

main.o: main.cpp functions.h variables.h simulator.h
	$(CC) $(CFLAGS) -c main.cpp

variables.o: variables.cpp variables.h
	$(CC) $(CFLAGS) -c variables.cpp

clean:
	rm -f *.o csim
