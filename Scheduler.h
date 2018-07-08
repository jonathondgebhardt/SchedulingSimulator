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
public:
	// Member variables
	std::queue<Process>* ready = new std::queue<Process>();
	std::priority_queue<Process>* incoming = new std::priority_queue<Process>();
	std::vector<Process>* terminated = new std::vector<Process>();
	int time;
	int quantum;

	Scheduler();
	Scheduler(const int quantum);
	Scheduler(const std::vector<Process> processes);
	Scheduler(const std::vector<Process> processes, const int quantum);
	~Scheduler();

	void updateReadyQueue();
};

#endif