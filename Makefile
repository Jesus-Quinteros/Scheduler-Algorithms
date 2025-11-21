all: main

main: main.o algorithms.o display.o
	g++ main.o algorithms.o display.o -o main -lraylib

main.o: algorithms.hpp
	g++ -c main.cpp

algorithms.o: algorithms.hpp
	g++ -c algorithms.cpp

display.o: algorithms.hpp
	g++ -c display.cpp

clean:
	rm -f main *.o

