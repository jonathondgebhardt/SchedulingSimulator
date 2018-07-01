#include "Process.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <stdlib.h>

std::vector<std::array<int, 3>> readInputFile(const std::string&);

// Expected args: input filename, type of scheduler

int main(int argc, char **argv)
{
	// Check for correct number of arguments.
	if(argc != 3)
	{
		std::cerr << "Requires two arguments: ./simulator [INPUT FILENAME] [SCHEDULER TYPE]\n";
		exit(1);
	}

	// Get arguments.
	std::string fileName = argv[1];	
	std::string schedulerType = argv[2];

	// Check for correct scheduler type.
	if(schedulerType != "FCFS" && schedulerType != "RR" && schedulerType != "MLFQ")
	{
		std::cerr << "Incorrect scheduler type: ./simulator [INPUT FILENAME] [FCFS|RR|MLFQ]\n";
		exit(1);
	}

	// Read file contents and store in vector.
	std::vector<std::array<int, 3>> fileContents = readInputFile(fileName);

	// Check for valid file contents.
	if(fileContents.size() == 0)
	{
		std::cerr << "Error reading file\n";
		exit(1);
	}

	// for(const auto a : fileContents)
	// {
	// 	for(const auto b : a)
	// 	{
	// 		std::cout << b << "\t";
	// 	}
	// 	std::cout << "\n";
	// }

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