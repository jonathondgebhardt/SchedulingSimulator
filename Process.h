//
// CEG4350 - Project 1: CPU Scheduling Simulator
// Summer 2018
// Instructor: Dr. Yong Pei
// Authors: Jonathon Gebhardt, Brittany Sommers-Woods
//

class Process
{
private:
	int pid;
	int arrival_time; // time in ms
	int burst_time; // time in ms
	enum class state{READY, RUNNING, TERMINATED};  

public:
	Process(int pid, int arrival_time, int burst_time);
	~Process();
};