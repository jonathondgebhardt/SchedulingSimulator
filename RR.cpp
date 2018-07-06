//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "RR.h"

RR::RR()
    : time(0), quantum(8)
{
}

RR::RR(const std::vector<Process> processes)
    : time(0), quantum(8)
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

RR::RR(const std::vector<Process> processes, int quantum)
    : time(0), quantum(quantum)
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

RR::~RR()
{
    // for(int i = 0; i < q->size(); ++i)
    // {
    //     q->pop();
    // }

    // delete q;
}

std::vector<Process> RR::run()
{
    std::cout << "Selected scheduling algorithm: RR\n";

	// Serve all processes to completion
	while(waiting->empty() == false)
	{
		Process p = waiting->front();
		waiting->pop();

        std::printf("PID %5d starts running at %5d\n", p.pid, time);

        if(p.remainingBurstTime > quantum)
        {
            time += quantum;
            p.remainingBurstTime -= quantum;
            waiting->push(p);

            std::printf("PID %5d is preempted by quantum and put back in waiting queue at %7d\n", p.pid, time);
        }
        else
        {
            time += p.remainingBurstTime;
            p.remainingBurstTime = 0;
            p.completionTime = time;
            terminated->push_back(p);

            std::printf("PID %5d has finished at %7d\n", p.pid, time);
        }
        
		
	}

	return *terminated;
}