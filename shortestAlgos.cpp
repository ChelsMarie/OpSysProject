#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include "shortestAlgos.h" 
#include "process.h" 

/*
alpha is used for exponential averaging to estimate CPU burst times
	initial guess is 1/labda

processes is a vector of process classes
	public functions:
		getLet()
		getArr()
		getBursts()
		getCPUTime()
		getIOTime()

*/
void srt(double alpha, std::vector<process> processes) {
	//add processes as interarrival times are reached
	std::vector<process> runList; 
	for(uint i = 0; i < processes.size(); i++) {
		if(processes[i].getArr() != 0) {
			runList.push_back(processes[i]);
		}
	}

	

}

void sjf(double alpha) {

}
