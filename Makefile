#
# CEG4350 - Project 1: CPU Scheduling Simulator
# Summer 2018
# Instructor: Dr. Yong Pei
# Authors: Jonathon Gebhardt, Brittany Sommers-Woods
#

all: simulator
	
simulator: process main process fcfs rr
	g++ Main.o Process.o FCFS.o RR.o -o simulator -std=c++11

main: Main.cpp
	g++ -c Main.cpp -std=c++11

process: Process.h Process.cpp
	g++ -c Process.h Process.cpp -std=c++11

fcfs: FCFS.h FCFS.cpp
	g++ -c FCFS.h FCFS.cpp -std=c++11

rr: RR.h RR.cpp
	g++ -c RR.h RR.cpp -std=c++11

clean:
	rm *o *h.gch simulator