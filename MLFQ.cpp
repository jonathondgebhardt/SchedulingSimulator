//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "MLFQ.h"

MLFQ::MLFQ(const std::vector<Process> processes)
    : Scheduler(processes)
{
    rr1 = new RR(8);
    rr2 = new RR(16);
    f = new FCFS();
}

// TODO: Implement destructor
MLFQ::~MLFQ()
{
    // for(int i = 0; i < q->size(); ++i)
    // {
    //     q->pop();
    // }

    // delete q;
}

// TODO: Should track which queue the process finished in
// TODO: Need to work around how C++ handles queues. Checking front/top on a queue
//       that is now empty, gets the last thing that is in the list.
std::vector<Process> MLFQ::run()
{
    Scheduler* s = rr1;
    Process currentProcess = incoming->top();
    incoming->pop();
    Process nextProcess;

    while(currentProcess.remainingBurstTime > 0)
    {
        int quantum = 8;

        if(currentProcess.priorityLevel == 1)
        {
            quantum = 16;
        }

        else if(currentProcess.priorityLevel == 2)
        {
            quantum = currentProcess.burstTime;
        }


        nextProcess = getNextProcess(quantum);

        if(nextProcess == currentProcess)
        {
            nextProcess = Process();
        }

        std::printf("PID %5d starts running at %5d\n", currentProcess.pid, time);

        if(currentProcess.timeServed < 0)
        {
            currentProcess.timeServed = time;
        }

        // Handle when scheduler is round robin
        if(currentProcess.priorityLevel != 2)
        {
            // Case 1: current process is preempted by incoming process -> push
            if(nextProcess.isNewArrival() && nextProcess.arrivalTime != -1 && time + quantum > nextProcess.arrivalTime && quantum < currentProcess.remainingBurstTime)
            {
                int delta = nextProcess.arrivalTime - time;
                time += delta;
                currentProcess.remainingBurstTime -= delta;

                // s->ready->push(currentProcess);
                preempt(&currentProcess);

                std::printf("PID %5d is preempted by PID %5d, pushed back\n", currentProcess.pid, nextProcess.pid);
            }
            
            else 
            {
                // Case 2: current process is preempted by quantum -> demote                
                if(quantum < currentProcess.remainingBurstTime)
                {
                    time += quantum;
                    currentProcess.remainingBurstTime -= quantum;
                    demote(&currentProcess);

                    std::printf("PID %5d is preempted by quantum, demoted\n", currentProcess.pid);
                }

                // Case 3: current process finishes -> terminate
                else
                {
                    time += currentProcess.remainingBurstTime;
                    currentProcess.remainingBurstTime = 0;
                    terminated->push_back(currentProcess);

                    std::printf("PID %5d has finished at %7d\n", currentProcess.pid, time);
                }
            }
        }

        else
        {
            // Case 1: current process is preempted by incoming process -> push
            if(nextProcess.arrivalTime != -1 && time + currentProcess.remainingBurstTime > nextProcess.arrivalTime)
            {
                int delta = nextProcess.arrivalTime - time;
                time += delta;
                currentProcess.remainingBurstTime -= delta;

                // s->ready->push(currentProcess);
                preempt(&currentProcess);

                std::printf("PID %5d is preempted by PID %5d, pushed back\n", currentProcess.pid, nextProcess.pid);
            }

            // Case 2: current process finishes -> terminate
            else
            {
                time += currentProcess.remainingBurstTime;
                currentProcess.remainingBurstTime = 0;
                terminated->push_back(currentProcess);

                std::printf("PID %5d has finished at %7d\n", currentProcess.pid, time);
            }

        } 
        
        if(nextProcess.pid != -1)
        {
            currentProcess = nextProcess;
        }

        s = getNextQueue();
    }

    return *terminated;
}

Scheduler* MLFQ::getNextQueue()
{
    Scheduler* temp;

    if(rr1->ready->empty() == false)
    {
        temp = rr1;
    }
    
    else if(rr2->ready->empty() == false)
    {
        temp = rr2;
    }

    else
    {
        temp = f;
    }
    
    return temp;
}

Process MLFQ::getNextProcess(int window)
{
    Process nextProcess;

    if(incoming->empty() == false && incoming->top().arrivalTime < time + window)
    {
        nextProcess = incoming->top();
        incoming->pop();
    }

    else if(rr1->ready->empty() == false)
    {
        nextProcess = rr1->ready->front();
        rr1->ready->pop();
    }

    else if(rr2->ready->empty() == false)
    {
        nextProcess = rr2->ready->front();
        rr2->ready->pop();
    }
    
    else if(f->ready->empty() == false)
    {
        nextProcess = f->ready->front();
        f->ready->pop();
    }

    return nextProcess;
}

void MLFQ::demote(Process* p)
{
    if(p->priorityLevel == 0)
    {
        p->priorityLevel = 1;
        rr2->ready->push(*p);
    }

    else
    {
        p->priorityLevel = 2;
        f->ready->push(*p);
    }
}

void MLFQ::preempt(Process* p)
{
    if(p->priorityLevel == 0)
    {
        rr1->ready->push(*p);
    }

    else if(p->priorityLevel == 1)
    {
        rr2->ready->push(*p);
    }

    else
    {
        p->priorityLevel = 2;
        f->ready->push(*p);
    }
}