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
std::vector<Process> MLFQ::run()
{
    Scheduler* s = rr1;
    Process currentProcess;
    Process nextProcess;

    // Serve all processes to completion.
    while(s->waiting->empty() == false)
    {
        // Get process from scheduler.
        currentProcess = s->waiting->front();
        s->waiting->pop();

        if(currentProcess.remainingBurstTime == currentProcess.burstTime)
		{
            // Find the amount of time for the first period of waiting
			currentProcess.timeServed = time;  
			currentProcess.waitTime = currentProcess.timeServed - currentProcess.arrivalTime;
		} 
        else
		{
			currentProcess.waitTime = currentProcess.waitTime + (time - currentProcess.pushBackTime);
		}

        std::printf("PID %5d starts running at %5d\n", currentProcess.pid, time);

        // Put back in appropriate scheduler queue.
        /*
        - A new process first enters Queue 0 (rr1) which is served in RR. When it
        gains CPU, process receives 8 ms (should be set already). If it does not
        finish in 8 ms, process is preempted and moved to Queue 1 (rr2).
        - At Queue 1 (rr2), process is again served in RR and receives 16 additional
        ms. If it still does not complete, it is preempted and moved to Queue 2 (f).
        - At Queue 2 (f), process is served in FCFS.
        - When a running process is preempted by a new process arriving at a higher
        priority queue, it will be put back to the end of its current queue. I.e., 
        its priority stays the same. A new full quantum will be given to it the next
        time it starts running.
        */

        // Get next process in line to determine appropriate queue
        if(rr1->waiting->empty() == false)
        {
            nextProcess = rr1->waiting->front();
        }
        else if(rr2->waiting->empty() == false)
        {
            nextProcess = rr2->waiting->front();
        }

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

                s->waiting->push(currentProcess);
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
                        rr2->waiting->push(currentProcess);
                        std::printf("PID %5d preempted by quantum, placed in Queue 1\n", currentProcess.pid);
                    }
                    else
                    {
                        f->waiting->push(currentProcess);
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
        if(rr1->waiting->empty() == false)
        {
            s = rr1;
        }
        else if(rr2->waiting->empty() == false)
        {
            s = rr2;
        }
        else
        {
            s = f;
        }
    }


    return *terminated;
}