all: simulator
	
simulator: process main
	g++ Process.o Main.o -o simulator

process: Process.h Process.cpp
	g++ -c Process.h Process.cpp

main: Main.cpp
	g++ -c Main.cpp

clean:
	rm *o simulator