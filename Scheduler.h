//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"

#include <queue>
#include <vector>
#include <iostream>


class Scheduler
{
protected:
    // Member variables
	std::queue<Process>* waiting = new std::queue<Process>();
	std::vector<Process>* terminated = new std::vector<Process>();
	int time;

public:
	Scheduler();
	Scheduler(const std::vector<Process> processes);
	~Scheduler();
};

#endif