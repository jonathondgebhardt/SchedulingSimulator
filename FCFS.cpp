//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "FCFS.h"

FCFS::FCFS(const std::vector<Process> processes)
{
    std::priority_queue<Process>& q = new std::priority_queue<Process>();
    for(const Process p : processes)
    {
        q.push(p);
    }

    std::cout << q.size() << "\n";
}

FCFS::~FCFS()
{
}

int FCFS::numProcesses()
{
    return q.size();
}

// void FCFS::print_queue()
// {
//     while(q.empty() == false)
//     {
//         std::cout << (Process) q.pop() << "\n";
//     }
// }

// std::ostream& operator<<(std::ostream& os, const FCFS& q)
// {
//     std::priority_queue<Process> temp_q = q;
// }