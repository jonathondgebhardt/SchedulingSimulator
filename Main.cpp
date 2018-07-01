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
	std::vector<std::array<int, 3>> fileContents = readInputFile("test/03.txt");

	std::cout << "result from reading:\n";

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
		std::string line;
		
		int index = 0;

		//while(getline(file, line, '\t'))
		while(getline(file, line))
		{
			// string line = "GeeksForGeeks is a must try";
     
			// // Vector of string to save tokens
			// vector <string> tokens;
			
			// // stringstream class check1
			// stringstream check1(line);
			
			// string intermediate;
			
			// // Tokenizing w.r.t. space ' '
			// while(getline(check1, intermediate, ' '))
			// {
			//     tokens.push_back(intermediate);
			// }
			
			// // Printing the token vector
			// for(int i = 0; i < tokens.size(); i++)
			//     cout << tokens[i] << '\n';

			std::array<int, 3> arr;
			std::stringstream ss(line);
			std::string intermediate;
			int x;

			while(getline(ss, intermediate, '\t'))
			{
				x = std::stoi(intermediate);
				std::cout << x << "\t";

				arr[index] = x;
				index = (index+1) % 3;
			}
			
			contents.push_back(arr);
			std::cout << "\n";

		}

		file.close();
	}

	else
	{
		std::cout << "Could not open file " << fileName << "\n";
	}

	return contents;
}