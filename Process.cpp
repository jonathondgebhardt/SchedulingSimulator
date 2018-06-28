#include "Process.h"

// int pid;
// 	int arrival_time; // time in ms
// 	int burst_time; // time in ms
// 	enum class state{READY, RUNNING, TERMINATED}; 

Process::Process(int pid, int arrival_time, int burst_time) 
	: pid(pid), arrival_time(arrival_time), burst_time(burst_time)
{

}

Process::~Process()
{

}