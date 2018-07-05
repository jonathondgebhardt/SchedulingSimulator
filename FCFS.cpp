//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "FCFS.h"

FCFS::FCFS(const std::vector<Process> processes)
{
    time = 0;

    for(const Process p : processes)
    {
        Process* temp = new Process(p.pid, p.arrivalTime, p.burstTime);
        waiting->push(*temp);
    }
}

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
    std::cout << "Selected scheduling algorithm: FCFS\n";

	// Serve all processes to completion
	while(waiting->empty() == false)
	{
		// Update time served and state
		Process p = waiting->top();

        std::printf("PID %5d starts running at %5d\n", p.pid, time);

		p.timeServed = time;
		*p.state = Process::State::TERMINATED;

		// Update time state
        time += p.burstTime;

		// Remove process from queue and add to vector
		waiting->pop();
		terminated->push_back(p);
	}

	return *terminated;
}