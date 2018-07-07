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

std::vector<Process> MLFQ::run()
{
    Scheduler s = *rr1;
    Process currentProcess;
    Process nextProcess;

    // Serve all processes to completion.
    while(s.waiting->empty() == false)
    {
        // Select scheduler based on which queue level and whether it is empty.
        if(rr1->waiting->empty() == false)
        {
            s = *rr1;
        }
        else if(rr2->waiting->empty() == false)
        {
            s = *rr2;
        }
        else
        {
            s = *f;
        }

        // Get process from scheduler.
        currentProcess = s.waiting->front();
        s.waiting->pop();

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

        // Ignore FCFS, which has a quantum of -1 by default.
        if(s.quantum != -1)
        {
            // If a process arrives while the current process is running, put back in
            // current level queue.
            if(nextProcess.arrivalTime < time + s.quantum)
            {
                // Update time tracking variables.
                int delta = nextProcess.arrivalTime - s.quantum;
                time += delta;
                currentProcess.remainingBurstTime -= delta;

                s.waiting->push(currentProcess);
            }
            // If a process finishes the entire quantum, put in the next level queue
            else
            {
                // Update time tracking variables.
                int currentQuantum = s.quantum;
                time += currentQuantum;
                currentProcess.remainingBurstTime -= currentQuantum;

                // Find appropriate queue.
                if(s.quantum == 8)
                {
                    rr2->waiting->push(currentProcess);
                }
                else
                {
                    f->waiting->push(currentProcess);
                }
            }
        }
        // Handle preemptive FCFS
        else
        {
            // If a process arrives while the current process is running, update time
            // using delta.
            if(currentProcess.remainingBurstTime > nextProcess.arrivalTime)
            {
                int delta = nextProcess.arrivalTime - time;
                currentProcess.remainingBurstTime -= delta;
                time += delta;

            }

            
        }

        std::cout << "Checking\n\t" << currentProcess << "\nagainst\n\t" << nextProcess << "\n";

        std::printf("PID %5d starts running at %5d\n", currentProcess.pid, time);


        // Only quit once all processes have been served
        // allProcessesServed = rr1.waiting->empty() == true && rr2.waiting->empty() == true && f.waiting->empty() == true;
    }


    return *terminated;
}