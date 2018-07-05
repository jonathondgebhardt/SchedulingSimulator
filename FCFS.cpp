//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "FCFS.h"

FCFS::FCFS(const std::vector<Process> processes)
    : time(0)
{
    std::priority_queue<Process> temp;

    for(const Process p : processes)
    {
        Process* pTemp = new Process(p.pid, p.arrivalTime, p.burstTime);
        temp.push(*pTemp);
    }

    while(temp.empty() == false)
    {
        waiting->push(temp.top());
        temp.pop();
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
        p.waitTime = p.timeServed - p.arrivalTime;
		*p.state = Process::State::TERMINATED;

		// Update time state
        time += p.burstTime;

        std::printf("PID %5d has finished at %7d\n", p.pid, time);

		// Remove process from queue and add to vector
		waiting->pop();
		terminated->push_back(p);
	}

	return *terminated;
}