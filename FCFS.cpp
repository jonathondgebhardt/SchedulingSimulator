//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "FCFS.h"

FCFS::FCFS()
{
}

FCFS::FCFS(const std::vector<Process> processes)
    : Scheduler(processes)
{
}

FCFS::~FCFS()
{
}

/// Use First Come First Serve algorithm (FCFS) to serve all 
/// processes to completion. FCFS is a non-preemptive scheduler that 
/// allows a process to execute for it's entire burst time.
std::vector<Process> FCFS::run()
{
	while(incoming->empty() == false || ready->empty() == false)
	{
		updateReadyQueue();

		Process p = ready->front();
		ready->pop();

        std::printf("PID %5d starts running at %5d\n", p.pid, time);

		// Update time tracking variables.
		p.timeServed = time;
        p.completionTime = p.burstTime + time;
        p.waitTime = p.timeServed - p.arrivalTime;

		// Update time state
        time += p.burstTime;

        std::printf("PID %5d has finished at %5d\n", p.pid, time);

		terminated->push_back(p);
	}

	return *terminated;
}