//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <stdlib.h>

#include "Process.h"
#include "FCFS.h"
#include "RR.h"
#include "MLFQ.h"

std::vector<std::array<int, 3>> readInputFile(const std::string&);
std::vector<Process> getProcesses(const std::vector<std::array<int, 3>>&);
double getAverageWaitingTime(const std::vector<Process>&);
double getAverageResponseTime(const std::vector<Process>&);
double getAverageTurnaroundTime(const std::vector<Process>&);
void printReport(const std::vector<Process>&);

int main(int argc, char **argv)
{
	// Check for correct number of arguments.
	if(argc != 3)
	{
		std::cerr << "Error -- Requires two arguments: ./simulator [INPUT FILENAME] [FCFS|RR|MLFQ]\n";
		return 1;
	}

	// Get arguments.
	std::string fileName = argv[1];	
	std::string schedulerType = argv[2];

	// Read file contents and store in vector.
	std::vector<std::array<int, 3>> fileContents = readInputFile(fileName);

	// Check for valid file contents.
	if(fileContents.size() == 0)
	{
		std::cerr << "Error -- Error reading file\n";
		return 1;
	}

	// Create a list of processes from file contents.
	std::vector<Process> processes = getProcesses(fileContents);

	// 'Run' processes according to scheduler type.
	std::vector<Process> servedProcesses;
	if(schedulerType == "FCFS")
	{
		std::cout << "Selected scheduling algorithm: FCFS\n";

		FCFS f(processes);
		servedProcesses = f.run();
	}
	else if(schedulerType == "RR")
	{
		std::cout << "Selected scheduling algorithm: RR\n";

		RR r(processes);
		servedProcesses = r.run();
	}
	else if(schedulerType == "MLFQ")
	{
		std::cout << "Selected scheduling algorithm: MLFQ\n";
		
		MLFQ m(processes);
		servedProcesses = m.run();
	}
	else
	{
		std::cerr << "Incorrect scheduler type: ./simulator [INPUT FILENAME] [FCFS|RR|MLFQ]\n";
		return 1;
	}

	// Print report showing statistics of scheduler.
	printReport(servedProcesses);

	return 0;
}

/// Reads input file and converts file contents to a vector of integer arrays.
std::vector<std::array<int, 3>> readInputFile(const std::string& fileName)
{
	std::vector<std::array<int, 3>> contents;
	std::ifstream file;
	file.open(fileName);
	
	try
	{
		// Attempt to open file.
		if (file.is_open())
		{
			std::string line;
			int index = 0;
			
			// Get line from file.
			while(getline(file, line))
			{
				// Tokenizing a string:
				// https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
				std::array<int, 3> arr;
				std::stringstream ss(line);
				std::string intermediate;
				int x;

				// Tokenize line and store in array.
				while(getline(ss, intermediate, '\t'))
				{
					x = std::stoi(intermediate);
					arr[index] = x;
					index = (index+1) % 3;
				}
				
				// Put line contents in vector.
				contents.push_back(arr);
			}
		}
		
	}
	// Handle non-numeric input and re-initialize return value.
	catch(std::invalid_argument& e)
	{
		std::cerr << "Error parsing file\n";
		contents = {};
	}

	file.close();

	return contents;
}

/// Populate vector with process objects with information provided by input vector.
std::vector<Process> getProcesses(const std::vector<std::array<int, 3>>& rawProcesses)
{
	std::vector<Process> processes;
	for(const auto a : rawProcesses)
	{
		int pid = a[0];
		int arrival_time = a[1];
		int burst_time = a[2];

		Process p(pid, arrival_time, burst_time);
		processes.push_back(p);
	}

	return processes;
}

/// Amount of time a process has been waiting in the ready queue.
double getAverageWaitingTime(const std::vector<Process>& servedProcesses)
{
	int totalTime = 0;

	for(const auto a : servedProcesses)
	{
		totalTime += a.waitTime;
	}

	return totalTime / (double) servedProcesses.size();
}

/// Amount of time from when a request was submitted until the first response is produced.
double getAverageResponseTime(const std::vector<Process>& servedProcesses)
{
	int totalTime = 0;

	for(const auto a : servedProcesses)
	{
		totalTime += a.timeServed - a.arrivalTime;
	}

	return totalTime / (double) servedProcesses.size();
}

/// Amount of time to execute a particular process.
double getAverageTurnaroundTime(const std::vector<Process>& servedProcesses)
{
	int totalTime = 0;

	for(const auto a : servedProcesses)
	{
		totalTime += a.completionTime - a.arrivalTime;
	}

	return totalTime / (double) servedProcesses.size();
}

/// Print a report showing time statistics.
void printReport(const std::vector<Process>& servedProcesses)
{
	double avgWaitTime = getAverageWaitingTime(servedProcesses);
	double avgResponseTime = getAverageResponseTime(servedProcesses);
	double avgTurnaroundTime = getAverageTurnaroundTime(servedProcesses);

	std::cout << "=========================================\n";
	std::printf("Average waiting time: %.3f\n", avgWaitTime);
	std::printf("Average response time: %.3f\n", avgResponseTime);
	std::printf("Average turnaround time: %.3f\n", avgTurnaroundTime);
	std::cout << "=========================================\n";
}