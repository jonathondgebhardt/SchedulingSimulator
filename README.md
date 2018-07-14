# CPU Scheduling Simulator
- Class: CEG4350 -- Operating Systems and Internals
- Semester: Summer 2018
- Instructor: Dr. Yong Pei

## Introduction

The CPU scheduler is the unsung hero behind the veil of the operating system. It's specification can vary depending on your requirements, but can range from ensuring a snappy response for the user or highest throughput for batch processing. The scheduler can create some unfortunate side effects though, like race conditions and deadlocks, but such issues are outside the scope of this project. The goal of this event-driven simulator is to better understand how different scheduling algorithms are implemented and see first hand how schedulers compare and perform against each other under reproducible environments.

Based on the project requirements, we have implemented First Come First Serve (FCFS), Round Robin (RR), and Multi Level Feedback Queue (MLFQ) scheduling algorithms. For more detail about our implementation and design decisions, see the project report under the resource directory.

## Getting started

First, make sure your system satisfies the prerequisties. Afterwards, unzip the archive and run 'make' in the unzipped directory. Lastly, see 'Running the tests' to run a scheduler on a test file.

### Prerequisites

- make
- g++
- std c++11

## Running the tests

After building the executable, run

```
./simulator [TEST_FILE_NAME] [FCFS|RR|MLFQ]
```

where [TEST_FILE_NAME] is the desired test file, and [FCFS|RR|MLFQ] is a scheduler type. Four tests cases have been included but you may provide your own. See 'Creating your own test' for guidance on formatting. 

### The included tests

Test 00 contains a non-numeric character and tests whether file input validation is working correctly.

Test 01 was taken from a course handout. This test case has arrival times and burst times set so that processes will propegate through each queue in MLFQ.

Test 02 was taken from a course handout. This simple case essentially serves as a base case.

Test 03 was taken from the project prompt.

Test 04 was derived from Test 01 but goes a little further. This test was designed so that one process arrives much later than the others, preempting a process in the lowest priority queue. This serves to test preemptive FCFS in MLFQ.

### Creating your own test

The test file should be formatted as follows:

```
[PID0]	[ARRIVAL_TIME0]	[BURST_TIME0]
[PID1]	[ARRIVAL_TIME1]	[BURST_TIME1]
...
[PIDn]	[ARRIVAL_TIMEn]	[BURST_TIMEn]
```

where each row is a group of three tab delimited integers pertaining to one process. PID (process identification) is a unique integer that identifies an arbitrary process. Arrival time is when a particular process requests CPU execution time. Burst time is how much time the process needs to execute.

## Versioning

GitHub: https://github.com/jonathondgebhardt/SchedulingSimulator

## Authors

- Jonathon Gebhardt
- Brittany Sommers-Woods

## Acknowledgments

- Thanks to PurpleBooth for a convenient template and an introduction to markdown!