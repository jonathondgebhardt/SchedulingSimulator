all: simulator
	
simulator: process main
	g++ Process.o Main.o -o simulator -std=c++11

process: Process.h Process.cpp
	g++ -c Process.h Process.cpp -std=c++11

main: Main.cpp
	g++ -c Main.cpp -std=c++11

clean:
	rm *o simulator