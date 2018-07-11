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

// TODO: Implement destructor
FCFS::~FCFS()
{
    // for(int i = 0; i < q->size(); ++i)
    // {
    //     q->pop();
    // }

    // delete q;
}

std::vector<Process> FCFS::run()
{
	// Serve all processes to completion
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