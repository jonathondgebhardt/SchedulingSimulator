//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "RR.h"

RR::RR()
    : Scheduler(8)
{
}

RR::RR(int quantum)
    : Scheduler(quantum)
{
}

RR::RR(const std::vector<Process> processes)
    : Scheduler(processes, 8)
{
}

RR::RR(const std::vector<Process> processes, int quantum)
    : Scheduler(processes, quantum)
{
}

// TODO: Implement destructor
RR::~RR()
{
    // for(int i = 0; i < q->size(); ++i)
    // {
    //     q->pop();
    // }

    // delete q;
}

/// Serve all processes to completion.
std::vector<Process> RR::run()
{
	while(incoming->empty() == false || ready->empty() == false)
	{
        updateReadyQueue();

		Process p = ready->front();
        ready->pop();	
		
	// Double checks that if a process happens to be pushed back while also being
	// the first process ran that it is put back in the correct place in the queue
	// rather than in the front of the queue by default
	if(p.pushBackTime > 0 && p.pushBackTime == time)
	{
		ready->push(p);
		continue;
	}
		// If the process has not ran at all yet the wait time is equal to the
		// amount of time served. Otherwise, the wait time is equal to the time
		// served added to the time difference from when the process was pushed
		// back to the waiting queue and the current time.
	if(p.remainingBurstTime == p.burstTime)
	{
            // Find the amount of time for the first period of waiting
		p.timeServed = time;  
		p.waitTime = time - p.arrivalTime;
	} 
        else
	{
		p.waitTime += time - p.pushBackTime;
	}
		
        std::printf("PID %5d starts running at %5d\n", p.pid, time);

        // If the remaining burst time of the process is greater than the designated quantum
        // then update the time for the desired quantum length and subtract the same amount
        // of time from the remaining burst time ofthe process and then push into the wait
        // queue again.
        if(p.remainingBurstTime > quantum)
        {
            time += quantum;
	    p.pushBackTime = time;
            p.remainingBurstTime -= quantum;
            ready->push(p);

            std::printf("PID %5d is preempted by quantum, pushed back\n", p.pid);
        }

        // Otherwise we update the time for the remainder of the burst time and set the
        // remaining burst to 0. The completion time is then set and the process is 
        // moved to the terminated queue.
        else
        {
            time += p.remainingBurstTime;
            p.remainingBurstTime = 0;
            p.completionTime = time;
            terminated->push_back(p);

            std::printf("PID %5d has finished at %5d\n", p.pid, time);
        }	
	}

	return *terminated;
}
