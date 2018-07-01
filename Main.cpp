//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

#include "Process.h"
#include "FCFS.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <stdlib.h>

std::vector<std::array<int, 3>> readInputFile(const std::string&);
std::vector<Process> getProcesses(const std::vector<std::array<int, 3>>&);

// Expected args: input filename, type of scheduler

int main(int argc, char **argv)
{
	// Check for correct number of arguments.
	if(argc != 3)
	{
		std::cerr << "Requires two arguments: ./simulator [INPUT FILENAME] [SCHEDULER TYPE]\n";
		return 1;
	}

	// Get arguments.
	std::string fileName = argv[1];	
	std::string schedulerType = argv[2];

	// Check for correct scheduler type.
	if(schedulerType != "FCFS" && schedulerType != "RR" && schedulerType != "MLFQ")
	{
		std::cerr << "Incorrect scheduler type: ./simulator [INPUT FILENAME] [FCFS|RR|MLFQ]\n";
		return 1;
	}

	// Read file contents and store in vector.
	std::vector<std::array<int, 3>> fileContents = readInputFile(fileName);

	// Check for valid file contents.
	if(fileContents.size() == 0)
	{
		std::cerr << "Error reading file\n";
		return 1;
	}

	std::vector<Process> processes = getProcesses(fileContents);

	for(Process a : processes)
	{
		// a.toString();
		std::cout << a << "\n";
	}

	return 0;
}

std::vector<std::array<int, 3>> readInputFile(const std::string& fileName)
{
	std::vector<std::array<int, 3>> contents;
	std::ifstream file;
	file.open(fileName);
	
	try
	{
		// Attempt to open file
		if (file.is_open())
		{
			std::string line;
			int index = 0;
			
			// Get line from file
			while(getline(file, line))
			{
				// Tokenizing a string:
				// https://www.geeksforgeeks.org/tokenizing-a-string-cpp/

				std::array<int, 3> arr;
				std::stringstream ss(line);
				std::string intermediate;
				int x;

				// Tokenize line and store in array
				while(getline(ss, intermediate, '\t'))
				{
					x = std::stoi(intermediate);
					arr[index] = x;
					index = (index+1) % 3;
				}
				
				// Put line contents in vector
				contents.push_back(arr);
			}
		}
		
	}
	// Handle non-number input
	catch(std::invalid_argument e)
	{
		std::cerr << "Error parsing file\n";
	}

	file.close();

	return contents;
}

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