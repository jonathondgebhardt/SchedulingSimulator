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
	RR* rr1;
	RR* rr2;
	FCFS* f;

public:
	MLFQ(const std::vector<Process> processes);
	~MLFQ();

	std::vector<Process> run();
	Scheduler* getNextQueue();
	Process getNextProcess(int window);
	int getQuantum(Process* p);
	void demote(Process* p);
	void preempt(Process* p);
};

#endif