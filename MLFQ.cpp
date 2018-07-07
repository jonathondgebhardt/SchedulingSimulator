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
    // TODO: Should make a parent scheduler class so we can use
    // any arbitrary scheduler
    Scheduler s;

	// Serve all processes to completion
    bool allProcessesServed = false;
    while(allProcessesServed)
    {
		Process p;
        
        // Select scheduler based on which queue level and whether it is empty

        // Get process from scheduler

        // Update time tracking vars

        // Put back in appropriate scheduler queue
        /*
            - A new process first enters Queue 0 (rr1) which is served in RR. When it
            gains CPU, process receives 8 ms (should be set already). If it does not
            finish in 8 ms, process is preempted and moved to Queue 1 (rr2).
            - At Queue 1 (rr2), process is again served in RR and receives 16 additional
            ms. If it still does not complete, it is preempted and moved to Queue 2 (f).
            - At Queue 2 (f), process is served in FCFS.
            - When a running process is preempted by a new process arrivnig at a higher
            priority queue, it will be put back to the end of its current queue. I.e., 
            its priority stays the same. A new full quantum will be given to it the next
            time it starts running.
        */

        std::printf("PID %5d starts running at %5d\n", p.pid, time);

        
        // Only quit once all processes have been served
        // allProcessesServed = rr1.waiting->empty() == true && rr2.waiting->empty() == true && f.waiting->empty() == true;
    }
	

	return *terminated;
}