//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "RR.h"
#include <queue>

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

RR::~RR()
{
}

/// Use Round Robin algorithm (RR) to serve all process to
/// completion. RR is a quantum preemptive scheduler that allows a
/// process to execute for a specified amount of time. Once that 
/// time expires, preempt the current process by putting it at
/// the end of the queue.
std::vector<Process> RR::run()
{
	while(incoming->empty() == false || ready->empty() == false)
	{

		updateReadyQueue();

		// If a process enters after a short break between processes, we need to 
		// update the time in order for it to be pushed to the ready queue appropriately
		if(!incoming->empty() && ready->empty() && incoming->top().arrivalTime > 0)
		{
			time = incoming->top().arrivalTime;
			continue;
		}

		Process p = ready->front();
		ready->pop();
		Process temp = ready->front();

		// Checks that the ready queue is not out of order if new processes have arrived
		// while other processes that were preempted were running. Fixes it if it is.
		if(temp.remainingBurstTime == temp.burstTime && p.pushBackTime > temp.arrivalTime && temp.burstTime != 0)
		{
			ready->push(p);
			p = temp;
			ready->pop();
		}

		// Checks that the queue is not out of order of the order for preempted processes.
		// Fixes it if it is.
		if(p.pushBackTime > temp.pushBackTime && temp.pushBackTime != 0)
		{
			ready->push(p);
			p = temp;
			ready->pop();
		}		
		
        	// Check to make sure that if a process executes is not pushed back to the top
		// of the queue when it shouldn't be -- keeps the first process from reentering
		// the ready queue before processes held in the waiting queue
		if(p.pushBackTime > 0 && p.pushBackTime == time && !ready->empty())
		{
			ready->push(p);
			continue;
		}

		// If the process has not ran at all yet the wait time is equal to the
		// amount of time served. Otherwise, the wait time is equal to the time
		// served added to the time difference from when the process was pushed
		// back to the waiting queue and the current time.
		if(p.isNewArrival() == true)
		{
			// Find the amount of time for the first period of waiting.
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
