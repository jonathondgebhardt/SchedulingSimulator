//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "MLFQ.h"

MLFQ::MLFW(const std::vector<Process> processes)
{
	time = 0;
	
	for(const Process p : processes)
	{
		Process* temp = new Process(p.pid, p.arrivalTime, p.burstTime);
		waiting-push(*temp);
}

MLFQ::~MLFQ()
{

}

std::vector<Process> MLFQ::run()
{


	return *terminated;
}
