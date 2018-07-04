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
        q->push(*temp);
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

void FCFS::process()
{
    Process p = q->top();
    q->pop();
    std::cout << p << "\n";
}