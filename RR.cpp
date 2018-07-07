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

std::vector<Process> RR::run()
{
	// Serve all processes to completion
	while(waiting->empty() == false)
	{
		Process p = waiting->front();
        waiting->pop();

        std::printf("PID %5d starts running at %5d\n", p.pid, time);

        // Find the amount of time for the first period of waiting
		p.timeServed = time;  
		
		// If the process has not ran at all yet the wait time is equal to the
		// amount of time served. Otherwise, the wait time is equal to the time
		// served added to the time difference from when the process was pushed
		// back to the waiting queue and the current time.
		if(p.remainingBurstTime == p.burstTime)
		{
			p.waitTime = p.timeServed - p.arrivalTime;
		} 
        
        else
		{
			p.waitTime = p.waitTime + (time - p.pushBackTime);
		}

        // If the remaining burst time of the process is greater than the designated quantum,
        // then update the time for the desired quantum length and subtract the same amount
        // of time from the remaining burst time of the process and then push into the wait
        // queue again.
        if(p.remainingBurstTime > quantum)
        {
            time += quantum;
	        p.pushBackTime = time;
            p.remainingBurstTime -= quantum;
            waiting->push(p);

            std::printf("PID %5d is preempted by quantum, returned to waiting queue at %5d\n", p.pid, time);
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

            std::printf("PID %5d has finished at %7d\n", p.pid, time);
        }
	}

	return *terminated;
}
