//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#ifndef RR_H
#define RR_H

#include "Process.h"
#include "Scheduler.h"

#include <queue>
#include <vector>
#include <iostream>


class RR : public Scheduler
{
protected:
	int quantum;

public:
	RR();
	RR(int quantum);
	RR(const std::vector<Process> processes);
	RR(const std::vector<Process> processes, int quantum);
	~RR();
	std::vector<Process> run();
};

#endif