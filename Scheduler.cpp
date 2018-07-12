//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "Scheduler.h"

Scheduler::Scheduler()
    : time(0), quantum(-1)
{
}

Scheduler::Scheduler(const int quantum)
    : time(0), quantum(quantum)
{
}

Scheduler::Scheduler(const std::vector<Process> processes)
    : time(0)
{
    // We'll use a priority queue to facilitate ordering processes by
    // arrival time.
    for(const Process p : processes)
    {
        Process* pTemp = new Process(p.pid, p.arrivalTime, p.burstTime);
        incoming->push(*pTemp);
    }
}

Scheduler::Scheduler(const std::vector<Process> processes, int quantum)
    : time(0), quantum(quantum)
{
    // We'll use a priority queue to facilitate ordering processes by
    // arrival time.
    for(const Process p : processes)
    {
        Process* pTemp = new Process(p.pid, p.arrivalTime, p.burstTime);
        incoming->push(*pTemp);
    }
}

// TODO: Implement destructor
Scheduler::~Scheduler()
{
    // for(int i = 0; i < q->size(); ++i)
    // {
    //     q->pop();
    // }

    // delete q;
}

/// Use the incoming queue to populate the ready queue.
void Scheduler::updateReadyQueue()
{
    if(incoming->empty() == false)
    {
        Process temp;
        do
        {
            temp = incoming->top();

            if(temp.arrivalTime <= time)
            {
                ready->push(temp);
                incoming->pop();
            }
        }
        while(temp.arrivalTime <= time && temp.pid != incoming->top().pid);
    }
}