//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "MLFQ.h"

MLFQ::MLFQ(const std::vector<Process> processes)
{
    rr1 = new RR(processes, 8);
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

    // Serve all processes to completion.
    while(rr1->incoming->empty() == false || s->ready->empty() == false)
    {
        rr1->updateReadyQueue();

        // Get process from scheduler.
        currentProcess = s->ready->front();
        s->ready->pop();
        
        if(currentProcess.remainingBurstTime == currentProcess.burstTime)
		{
            // Find the amount of time for the first period of waiting.
			currentProcess.timeServed = time;  
			currentProcess.waitTime = time - currentProcess.arrivalTime;
		} 
        else
		{
			currentProcess.waitTime += time - currentProcess.pushBackTime;
		}

        std::printf("PID %5d starts running at %5d\n", currentProcess.pid, time);

        nextProcess = getNextProcess();

        // Ignore FCFS, which has a quantum of -1 by default.
        if(s->quantum != -1)
        {
            // If a process arrives while the current process is running, put back in
            // current level queue but only if the new process is a 'new' arrival.
            if(nextProcess.burstTime == nextProcess.remainingBurstTime 
                && nextProcess.arrivalTime < time + s->quantum)
            {
                // Update time tracking variables.
                // int delta = nextProcess.arrivalTime - s.quantum;
                int delta = nextProcess.arrivalTime - time;
                time += delta;
                currentProcess.remainingBurstTime -= delta;

                s->ready->push(currentProcess);
                std::printf("PID %5d preempted by PID %5d, pushed to current Queue\n", currentProcess.pid, nextProcess.pid);
            }
            
            // If a process is not preempted by another one, handle accordingly.
            else
            {
                // Update time tracking variables.
                int currentQuantum = s->quantum;
                if (currentProcess.remainingBurstTime > currentQuantum)
                {
                    time += currentQuantum;
                    currentProcess.pushBackTime = time;
                    currentProcess.remainingBurstTime -= currentQuantum;
                }
                else
                {
                    time += currentProcess.remainingBurstTime;
                    currentProcess.remainingBurstTime = 0;
                }
                
                // Find appropriate queue.
                if(currentProcess.remainingBurstTime > 0)
                {
                    if(s->quantum == 8)
                    {
                        rr2->ready->push(currentProcess);
                        std::printf("PID %5d preempted by quantum, placed in Queue 1\n", currentProcess.pid);
                    }
                    else
                    {
                        f->ready->push(currentProcess);
                        std::printf("PID %5d preempted by quantum, placed in Queue 2\n", currentProcess.pid);
                    }
                }
                else
                {
                    currentProcess.completionTime = time;
                    terminated->push_back(currentProcess);
                    std::printf("PID %5d has finished at %5d\n", currentProcess.pid, time);
                }
            }
        }
        // TODO: Handle preemptive FCFS
        else
        {
            time += currentProcess.remainingBurstTime;
            currentProcess.remainingBurstTime = 0;
            currentProcess.completionTime = time;
            terminated->push_back(currentProcess);

            std::printf("PID %5d has finished at %5d\n", currentProcess.pid, time);
        }

        // Select scheduler based on which queue level and whether it is empty.
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
        nextProcess = rr1->incoming->top();
    }

    return nextProcess;
}