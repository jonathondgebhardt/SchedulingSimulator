//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#pragma once

#include <iostream>

class Process
{
public:
	enum class State{READY, RUNNING, TERMINATED}; 

	Process(int pid, int arrivalTime, int burstTime);
	Process(int pid, int arrivalTime, int burstTime, State state);
	~Process();
	friend std::ostream& operator<<(std::ostream& os, Process& p);
	int getPID();
	int getArrivalTime();
	int getBurstTime();
	int getRemainingBurstTime();
	// std::string getState();

private:
	int pid;
	int arrivalTime; // time in ms
	int burstTime; // time in ms
	int remainingBurstTime;
	State state;
};