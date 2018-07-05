//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#ifndef FCFS_H
#define FCFS_H

#include "Process.h"

#include <queue>
#include <vector>
#include <iostream>


class FCFS
{
public:
	// Member variables
	std::priority_queue<Process>* waiting = new std::priority_queue<Process>();
	std::vector<Process>* terminated = new std::vector<Process>();
	int time;

	FCFS(const std::vector<Process> processes);
	~FCFS();
	std::vector<Process> run();
};

#endif