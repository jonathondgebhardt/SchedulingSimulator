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
// TODO: Processes are popped even if they haven't arrived yet.
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
            /* 
                Problem is in this if statement. 
            
                Based on test case 00, PID 1 arrives at 0 and executes for 1 ms
                before it's preempted by PID 2. So ready queue transitions like this: 
                    {1} -> {2, 1}
                
                I accomplished this on lines 85 and 86. I update the ready queue, which
                how ever many processes have arrived since the time updated and pushes
                them to the ready queue. This fine when there's only ever one process
                in the queue.

                PID executes for 1 ms before it's preempted by PID 3. So the ready queue
                should transition like this:
                    {2, 1} -> {3, 1, 2}
                but actually transitions like this:
                    {2, 1} -> {1, 3, 2}

                We effectively need to put the new process at the beginning of the queue
                and the preempted process at the end, but how do?
            */
            // Case 1: current process is preempted by incoming process -> push
            if(nextProcess.timeServed < 0 && time + s->quantum > nextProcess.arrivalTime)
            {
                int delta = nextProcess.arrivalTime - time;
                time += delta;
                currentProcess.remainingBurstTime -= delta;

                updateReadyQueue(rr1);
                s->ready->push(currentProcess);

                std::printf("PID %5d is preempted PID %5d, pushed back\n", currentProcess.pid, nextProcess.pid);
            }
            
            else 
            {
                // Case 2: current process is preempted by quantum -> demote                
                if(time + s->quantum < currentProcess.remainingBurstTime)
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
    if(currentQuantum == -8)
    {
        rr2->ready->push(*p);
    }

    else if(currentQuantum == -16)
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