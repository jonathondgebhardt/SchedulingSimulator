//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "MLFQ.h"

MLFQ::MLFQ(const std::vector<Process> processes)
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

MLFQ::~MLFQ()
{
    // for(int i = 0; i < q->size(); ++i)
    // {
    //     q->pop();
    // }

    // delete q;
}

std::vector<Process> MLFQ::run()
{
    std::cout << "Selected scheduling algorithm: RR\n";

	// Serve all processes to completion
	while(waiting->empty() == false)
	{
           
		
	}

	return *terminated;
}