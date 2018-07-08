//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#ifndef MLFQ_H
#define MLFQ_H

#include "Process.h"
#include "Scheduler.h"
#include "RR.h"
#include "FCFS.h"

#include <queue>
#include <vector>
#include <iostream>


class MLFQ : public Scheduler
{
protected:
	// Member variables
	RR* rr1;
	RR* rr2;
	FCFS* f;

public:
	// Member functions
	MLFQ(const std::vector<Process> processes);
	~MLFQ();
	std::vector<Process> run();
};

#endif