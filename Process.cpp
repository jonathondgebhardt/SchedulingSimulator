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

// Overloading <<
// https://msdn.microsoft.com/en-us/library/1z2f6c2k.aspx
std::ostream& operator<<(std::ostream& os, Process& p)
{  
    // os << dt.mo << '/' << dt.da << '/' << dt.yr;

	os << "PID: " << p.getPID() << ", burst time: " << p.getBurstTime() << ", arrival time: " << p.getArrivalTime() 
		<< ", remaining time: " << p.getRemainingBurstTime() << ", state: UNKNOWN";
    return os;  
}

int Process::getPID()
{
	return pid;
}

int Process::getArrivalTime()
{
	return arrivalTime;
}

int Process::getBurstTime()
{
	return burstTime;
}

int Process::getRemainingBurstTime()
{
	return remainingBurstTime;
}

// std::string Process::getState()
// {
// 	if(state == State::READY)
// 	{
// 		return "READY";
// 	}
// }