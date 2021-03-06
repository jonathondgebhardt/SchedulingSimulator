//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>

class Process
{
public:
	int pid;
	int arrivalTime;
	int burstTime;
	int remainingBurstTime;
	int timeServed;
	int waitTime;
	int completionTime;
	int pushBackTime;
	int priorityLevel;

	Process();
	Process(int pid, int arrivalTime, int burstTime);
	~Process();
	
	bool isNewArrival();
	friend std::ostream& operator<<(std::ostream& os, const Process& p);
	friend bool operator<(const Process& a, const Process& b);
	friend bool operator==(const Process& a, const Process& b);
};

#endif
