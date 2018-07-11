//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "Process.h"

#include <iostream>
#include <string>

Process::Process()
	: pid(-1), arrivalTime(-1), burstTime(-1), remainingBurstTime(-1),
		timeServed(-1), waitTime(-1), completionTime(-1)
{
}

Process::Process(int pid, int arrivalTime, int burstTime) 
	: pid(pid), arrivalTime(arrivalTime), burstTime(burstTime), remainingBurstTime(burstTime), 
		timeServed(0), waitTime(0), completionTime(0), pushBackTime(0)
	  
{
}

Process::~Process()
{
}

bool Process::isNewArrival()
{
	return burstTime == remainingBurstTime;
}

// Overloading '<<' for easier printing
// https://msdn.microsoft.com/en-us/library/1z2f6c2k.aspx
std::ostream& operator<<(std::ostream& os, const Process& p)
{
	os << "PID: " << p.pid << ", arrival time: " << p.arrivalTime << ", burst time: " << p.burstTime
		<< ", remaining time: " << p.remainingBurstTime << ", time served: " << p.timeServed;

	// switch(*p.state)
	// {
	// 	case Process::State::READY:
	// 		os << "READY";
	// 		break;
	// 	case Process::State::RUNNING:
	// 		os << "RUNNING";
	// 		break;
	// 	case Process::State::TERMINATED:
	// 		os << "TERMINATED";
	// 		break;
	// 	default:
	// 		os << "UNKNOWN";
	// 		break;
	// }
	
    return os;  
}

// Overloading '<' for priority queue
// https://stackoverflow.com/questions/9178083/priority-queue-for-user-defined-types
bool operator<(const Process& a, const Process& b) 
{
	if(a.burstTime == a.remainingBurstTime && b.burstTime == b.remainingBurstTime)
	{
		return a.arrivalTime > b.arrivalTime;
	}

	if(a.burstTime == a.remainingBurstTime)
	{
		return false;
	}

	else
	{
		return true;
	}
}

bool operator==(const Process& a, const Process& b) 
{
  return a.pid == b.pid;
}
