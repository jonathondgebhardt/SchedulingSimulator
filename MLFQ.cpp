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

MLFQ::~MLFQ()
{
}

/// Use Multi Level Feedback Queue algorithm (MLFQ) to serve
/// all processes to completion. MLFQ is a tiered scheduling 
/// algorithm that utilizes priority and aging. Processes in 
/// queue 0 and queue 1 are served in Round Robin (RR) and 
/// processes in queue 2 are served in First Come First Serve 
/// (FCFS).
std::vector<Process> MLFQ::run()
{
    Process currentProcess = incoming->top();
    incoming->pop();
    Process nextProcess;

    while(currentProcess.remainingBurstTime > 0)
    {
        // Get an appropriate time window for current process. This is critical
        // for getting an appropriate nextProcess. We only want the nextProcess
        // if it 'arrives' while currentProcess is executing, no matter the
        // priority of currentProcess. This also simplifies handling which
        // priority level currentProcess is.
        int quantum = getQuantum(&currentProcess);
        nextProcess = getNextProcess(quantum);

        // Because of how C++ handles queues, if a queue is empty and you call
        // front/top, it will retrieve the last Process that was in the queue.
        // Make nextProcess a default Process if this is the case.
        if(nextProcess == currentProcess)
        {
            nextProcess = Process();
        }

        std::printf("PID %5d starts running at %5d\n", currentProcess.pid, time);

        // Case 1: Current process is a new arrival
        if(currentProcess.isNewArrival() == true)
        {
            // Case 1a: Served full quantum -> demoted
            if(currentProcess.remainingBurstTime > quantum)
            {
                time += quantum;
                currentProcess.remainingBurstTime -= quantum;
                demote(&currentProcess);

                std::printf("PID %5d is preempted by quantum, demoted\n", currentProcess.pid);
            }

            // Case 1b: Finishes -> terminated
            else
            {
                time += currentProcess.remainingBurstTime;
                currentProcess.remainingBurstTime = 0;
                terminated->push_back(currentProcess);

                std::printf("PID %5d has finished at %5d\n", currentProcess.pid, time);
            }
            
        }

        // Case 2: Next Process is a new arrival
        else if(nextProcess.pid != -1 && nextProcess.isNewArrival() == true)
        {
            int delta = nextProcess.arrivalTime - time;

            // Case 2a: Current process doesn't get full quantum -> prempt
            if(delta < quantum)
            {
                time += delta;
                currentProcess.remainingBurstTime -= delta;
                preempt(&currentProcess);

                std::printf("PID %5d is preempted by PID %5d, pushed back\n", currentProcess.pid, nextProcess.pid);
            }

            // Case 2b: Not enough time to finish -> demote
            else if(currentProcess.remainingBurstTime > quantum)
            {
                time += quantum;
                currentProcess.remainingBurstTime -= quantum;
                demote(&currentProcess);

                std::printf("PID %5d is preempted by quantum, demoted\n", currentProcess.pid);
            }

            // Case 2c: Enough time to finish -> terminate
            else
            {
                time += currentProcess.remainingBurstTime;
                currentProcess.remainingBurstTime = 0;
                terminated->push_back(currentProcess);

                std::printf("PID %5d has finished at %5d\n", currentProcess.pid, time);
            }
        }

        // Case 3: Neither process is new
        else
        {
            // Case 3a: Not enough time to finish -> demote
            if(currentProcess.remainingBurstTime > quantum)
            {
                time += quantum;
                currentProcess.remainingBurstTime -= quantum;
                demote(&currentProcess);

                std::printf("PID %5d is preempted by quantum, demoted\n", currentProcess.pid);
            }

            // Case 3b: Enough time to finish -> terminate
            else
            {
                time += currentProcess.remainingBurstTime;
                currentProcess.remainingBurstTime = 0;
                terminated->push_back(currentProcess);

                std::printf("PID %5d has finished at %5d\n", currentProcess.pid, time);
            }
        }

        // Handle the special case where nextProcess is a default process.
        if(nextProcess.pid != -1)
        {
            currentProcess = nextProcess;

	    // Updates time to account for break between processes if one exists
	    if(nextProcess.arrivalTime > time)
	    {
		    time = nextProcess.arrivalTime;
	    }
        }
    }

    return *terminated;
}

/// Retrieves the next appropriate process so we can know how to handle preemption.
Process MLFQ::getNextProcess(int window)
{
    Process nextProcess;

    // Prioritize new processes that will arrive within the current process's
    // window of execution.
    if(incoming->empty() == false && incoming->top().arrivalTime <= time + window)
    {
        nextProcess = incoming->top();
        incoming->pop();
    }

    // Handles if a process is entered after a break between processes
    else if(!incoming->empty() && rr1->ready->empty() && incoming->top().remainingBurstTime == incoming->top().burstTime && rr2->ready->empty() && f->ready->empty())
    {
	    nextProcess = incoming->top();
	    incoming->pop();
    }

    // Otherwise, grab the next priority level process.
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

/// Retrieves an appropriate quantum depending on p's priority level or required
/// execution time.
int MLFQ::getQuantum(Process* p)
{
    int quantum = 8;

    if(p->priorityLevel == 1)
    {
        quantum = 16;
    }

    // Handle lowest level priority process or if a process only needs a 
    // short amount of execution time.
    if(p->remainingBurstTime < quantum || p->priorityLevel == 2)
    {
        quantum = p->remainingBurstTime;
    }

    return quantum;
}

/// Demotes a process down one priority level.
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

/// Preempts a process by pushing it to the back of it's current
/// priority queue.
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
