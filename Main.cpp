#include "Process.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>

std::vector<std::array<int, 3>> readInputFile(const std::string&);

// Expected args: input filename, type of scheduler

int main(int argc, char **argv)
{
	std::vector<std::array<int, 3>> fileContents = readInputFile("test/00.txt");

	for(const auto a : fileContents)
	{
		for(const auto b : a)
		{
			std::cout << b << "\t";
		}

		std::cout << "\n";
	}

	return 0;
}

std::vector<std::array<int, 3>> readInputFile(const std::string& fileName)
{
	std::vector<std::array<int, 3>> contents;
	std::ifstream file;
	file.open(fileName);
	
	if (file.is_open())
	{
		std::string item;
		
		int index = 0;

		while(getline(file, item, '\t'))
		{
			std::array<int, 3> arr;

			std::stringstream ss(item);
			int x;
			ss >> x;
			
			if(index == 2)
			{
				contents.push_back(arr);
			}

			arr[index] = x;

			index = (index+1) % 3;
		}

		file.close();
	}

	else
	{
		std::cout << "Could not open file" << fileName << "\n";
	}

	return contents;
}