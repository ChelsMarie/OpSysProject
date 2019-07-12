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
void sjf(double alpha, std::vector<process> processes) {
	//add processes as interarrival times are reached
	std::vector<process> queue; 
	//as interarrival times are reached, add process to q  
	for(uint i = 0; i < processes.size(); i++) {

		std::cout << "Process" << processes[i].getLet() << "[NEW] (arrival time: ";
		std::cout << processes[i].getArr() << "ms )" << processes[i].getBursts();
		std::cout << "CPU bursts (tau " << processes[i].getCPUTime() << ") << std::endl; 

		if(processes[i].getArr() == 0) {
			runList.push_back(processes[i]);
			
		}
	}
	int t = -1; //int to count up time 	
	while(t++) { //time loop
		
		std::cout << "time " << t << "ms:";
		if(t == 0);
	}
	
	
			

}

void srt(double alpha) {

}
