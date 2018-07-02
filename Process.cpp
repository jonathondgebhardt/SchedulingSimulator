//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "Process.h"

#include <iostream>
#include <string>

Process::Process(int pid, int arrivalTime, int burstTime) 
	: pid(pid), arrivalTime(arrivalTime), burstTime(burstTime), remainingBurstTime(burstTime)
{
	State state = State::READY;
}

Process::Process(int pid, int arrivalTime, int burstTime, State state) 
	: pid(pid), arrivalTime(arrivalTime), burstTime(burstTime), remainingBurstTime(burstTime), state(state)
{
}

Process::~Process()
{
}

// Overloading '<<' for easier printing
// https://msdn.microsoft.com/en-us/library/1z2f6c2k.aspx
std::ostream& operator<<(std::ostream& os, const Process& p)
{  
    // os << dt.mo << '/' << dt.da << '/' << dt.yr;

	os << "PID: " << p.pid << ", arrival time: " << p.arrivalTime << ", burst time: " << p.burstTime
		<< ", remaining time: " << p.remainingBurstTime << ", state: ";

	switch(p.state)
	{
		case Process::State::READY:
			os << "READY";
			break;
		case Process::State::RUNNING:
			os << "RUNNING";
			break;
		case Process::State::TERMINATED:
			os << "TERMINATED";
			break;			
	}
	
    return os;  
}

// Overloading '<' for priority queue
// https://stackoverflow.com/questions/9178083/priority-queue-for-user-defined-types
bool operator<(const Process& a, const Process& b) {
  return a.arrivalTime > b.arrivalTime;
}