//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#ifndef RR_H
#define RR_H

#include "Process.h"

#include <queue>
#include <vector>
#include <iostream>


class RR
{
public:
	// Member variables
	std::queue<Process>* waiting = new std::queue<Process>();
	std::vector<Process>* terminated = new std::vector<Process>();
	int time;
    int quantum;

	RR();
	RR(int quantum);
	RR(const std::vector<Process> processes);
	RR(const std::vector<Process> processes, int quantum);
	~RR();
	std::vector<Process> run();
};

#endif