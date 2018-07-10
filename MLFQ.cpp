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
    Process currentProcess;
    Process nextProcess;

    while(incoming->empty() == false || s->ready->empty() == false)
    {
        updateReadyQueue(s);

        currentProcess = s->ready->front();
        s->ready->pop();

        nextProcess = getNextProcess();

        std::printf("PID %5d starts running at %5d\n", currentProcess.pid, time);

        if(currentProcess.timeServed < 0)
        {
            currentProcess.timeServed = time;
        }

        // Update time
        // Handle when s is round robin
        if(s->quantum != -1)
        {
            // Case 1: current process is preempted by incoming process -> push
            if(nextProcess.burstTime == nextProcess.remainingBurstTime && time + s->quantum > nextProcess.arrivalTime)
            {
                int delta = nextProcess.arrivalTime - time;
                time += delta;
                currentProcess.remainingBurstTime -= delta;

                // updateReadyQueue(rr1);
                s->ready->push(currentProcess);

                std::printf("PID %5d is preempted PID %5d, pushed back\n", currentProcess.pid, nextProcess.pid);
            }
            
            else 
            {
                // Case 2: current process is preempted by quantum -> demote                
                if(s->quantum < currentProcess.remainingBurstTime)
                {
                    time += s->quantum;
                    currentProcess.remainingBurstTime -= s->quantum;
                    demote(&currentProcess, s->quantum);

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
            // Case 1: current process is preempted by incoming queue -> push
            if(time + currentProcess.remainingBurstTime > nextProcess.arrivalTime)
            {
                int delta = nextProcess.arrivalTime - time;
                time += delta;
                currentProcess.remainingBurstTime -= delta;

                updateReadyQueue(rr1);
                s->ready->push(currentProcess);

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

        s = getNextQueue();  
    }

    return *terminated;
}

// TODO: Will return a queue even if the next process in line hasn't
// 'arrived' yet.
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

Process MLFQ::getNextProcess()
{
    Process nextProcess;

    if(rr1->ready->empty() == false)
    {
        nextProcess = rr1->ready->front();
    }

    else if(rr2->ready->empty() == false)
    {
        nextProcess = rr2->ready->front();
    }
    
    else if(f->ready->empty() == false)
    {
        nextProcess = f->ready->front();
    }

    else
    {
        nextProcess = incoming->top();
    }

    return nextProcess;
}

void MLFQ::demote(Process* p, int currentQuantum)
{
    if(currentQuantum == 8)
    {
        rr2->ready->push(*p);
    }

    else
    {
        f->ready->push(*p);
    }
}

// void MLFQ::preempt(Process* p, Scheduler* s)
// {
    
//     while(incoming->top().arrivalTime <= time)
//     {

//     }

// }