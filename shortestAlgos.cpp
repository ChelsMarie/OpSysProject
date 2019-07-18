//Project by Chelsea Bovell (bovelc) and George Tate (tateg)

#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
#include "shortestAlgos.h" 
#include "process.h" 

int inCS = 0;
int csTime = 0;

std::string getQueue(std::vector<process> queue) {
	std::string q = " [Q";
	for(int i = 0; i < queue.size(); i++) {
		q += " " + queue[i].getLet(); 
	}
	q += "]";
	return(q);
}

std::string getStart(int t) {
	std::string message = "time " + std::to_string(t) + "ms: ";
	return message;
}
/*

type is the algo being run (sjf or srt)
t is time
queue is the processes in queue
inIO is the processes in IO (sorted by alphabetical order)
NIQ stands for "Not In Queue" and is for processes neither in queue or in IO

*/

//for preemptions that happen as a main event
void checkPreempt(process * usingCPU, std::vector<process> &queue, int t) {
	
	int tl = usingCPU -> getCPUFinTime() - t;
	for(int i = 0; i < queue.size(); i++) {
		if(queue[i].getCPUTime() < tl) {
			std::string message = getStart(t);
			usingCPU -> setState("ready");
			usingCPU -> insertCPUTime(tl);
			process * oldUser = usingCPU;
			usingCPU = &queue[i];
			usingCPU -> setState("ready");		
		}
	}
	std::string message;

}

//for preemptions that happen as the result of another event (arrival or end of IO)
std::string preempt(process * usingCPU, std::vector<process> &prev, std::vector<process> &queue, \
int spot, int tl)
  {
	char oldLet = usingCPU -> getLet();
	usingCPU -> setState("ready");
	usingCPU -> insertCPUTime(tl);
	queue.insert(queue.begin(), prev[spot]);
	usingCPU = &queue[0];
	usingCPU -> setState("ready");
	inCS = csTime;
	std::string message = "preempting " + std::to_string(oldLet) + getQueue(queue);
	return(message);
}



void termProcess(process p, int t, std::vector<process> queue) {
	std::string message = getStart(t);
	message += "Process " + std::to_string(p.getLet()) + " terminated" + getQueue(queue);
	std::cout << message << std::endl;
}


void finishIO(std::string alg, std::vector<process> &inIO, std::vector<process> &queue, \
 process * usingCPU, int t) {
	for(int i = 0; i < inIO.size(); i++) {
		if(inIO[i].getIOFinTime() == t) {
			inIO[i].setState("ready");
			std::string message = getStart(t);
			message += "Process " + inIO[inIO.size()-1].getLet();
			message += "(tau "+std::to_string(inIO[inIO.size()-1].getTau())+"ms) ";
			message += "complete I/O; ";
			if(alg == "sjf") {
				int tl = (usingCPU -> getCPUFinTime()) - t; 	
				if(inIO[i].getCPUTime() < tl){
					message += preempt(usingCPU, inIO, queue, i, tl);	

				}
			}
			else {
				message += "added back to ready queue" + getQueue(queue);
			}
			std::cout << message << std::endl;
			if(inIO[i].getBursts() != 0) {
				queue.push_back(inIO[i]);
				std::sort(queue.begin(), queue.end());
			} else {
				termProcess(inIO[i], t, queue);
			} 
			inIO.erase(inIO.begin()+i);	
		}
	}
}

//gets called in finishCPU()
void recalcTau(std::vector<process> queue, std::vector<process> inIO, \
 std::vector<process>::iterator it, int t, double alpha) {
	it -> setNewTau(t, alpha);
	std::string message =  getStart(t) + "Process";
	message += "Recalculated tau = " + std::to_string(it -> getTau()) + 
	message +=  "ms for process" + it -> getLet(); 
	message += getQueue(queue);
	std::cout << message << std::endl;
}

void finishCPU(int t, double alpha, process * usingCPU, std::vector<process> &queue, \
 std::vector<process> &inIO) 
{
	if(usingCPU != NULL && usingCPU -> getCPUFinTime() == t) {
		std::vector<process>::iterator it;
		it = std::find(queue.begin(), queue.end(), *usingCPU);
		std::string message = getStart(t); 
		message += "Process " + std::to_string(it -> getLet()) + " (tau ";
		message += std::to_string(it -> getTau()) + ") completed a CPU burst;";
		message += std::to_string(it -> getBursts()) + " to go" + getQueue(queue); 
		if(it != queue.end()) {
			it -> setState("blocked");	
			it -> setIOFinTime(t);
			inIO.push_back(*it);
			it = inIO.end()-1;
			queue.erase(it);
			message +=  getStart(t) + "Process" + it -> getLet();
			message += " switching out of CPU; will block on I/O until time ";
			message += std::to_string(it -> getIOFinTime());
			message += getQueue(queue); 
		}
		recalcTau(inIO, queue, it, t, alpha);
		std::cout << message << std::endl;
	}
}

void addProcesses(std::string alg, int t, std::vector<process> &NIQ, std::vector<process> &queue, \
 process * usingCPU) {
	//check if any process arrive for the first time
	for(int i = 0; i < NIQ.size(); i++) {
		if(NIQ[i].getArr() == t) { 
			std::string message = "";
			//queue.push_back(NIQ[i]);	
			message += "time " + std::to_string(t) + "ms: Process " + NIQ[i].getLet(); 
			message  += "(tau " + std::to_string(NIQ[i].getTau()) +  " ms) arrived;";
		
			if(alg == "sjf") {
				int tl = (usingCPU -> getCPUFinTime()) - t; 	
				if(NIQ[i].getCPUTime() < tl){
					message += preempt(usingCPU, NIQ, queue, i, tl);	
				}
			}
			else {
				message += " added to ready queue";
			}
			message += getQueue(queue);
			NIQ.erase(NIQ.begin()+i);
			i--; //decrement i to prevent the next process getting skipped
			//sort queue in decreasing order by next burst time
			std::cout << message << std::endl;
		}
	}
}


void startCPU(int t, std::vector<process> queue, process * usingCPU) {
		
	//check if process begins using cpu
	if(usingCPU == NULL) { //if nobody is using the cpu
		std::string message = "";
		queue[0].setState("running");
		queue[0].setCPUFinTime(t);
		usingCPU = &queue[0];
		message += "time: " + std::to_string(t) + " ms: Process " + usingCPU -> getLet();
		message += " (tau " + std::to_string(usingCPU -> getTau()) + ") started using \
		 the CPU for " + std::to_string(usingCPU -> getCPUTime()) + "ms burst";
		message += getQueue(queue);
		std::cout << message << std::endl;  
	}
}


/*
alpha is used for exponential averaging to estimate CPU burst times
	initial guess is 1/labda

processes is a vector of process classes
	see process.h and process.cpp for details
*/
void sjf(double alpha, std::vector<process> processes, int cs) {
	std::sort(processes.begin(), processes.end(), letSort);
	csTime = cs;
	//add processes as interarrival times are reached
	std::vector<process> queue; 
	std::vector<process> inIO;
	process * usingCPU = NULL; 
	//as interarrival times are reached, add process to q  
	for(uint i = 0; i < processes.size(); i++) {

		std::cout << "Process" << processes[i].getLet() << "[NEW] (arrival time: ";
		std::cout << processes[i].getArr() << "ms )" << processes[i].getBursts();
		std::cout << "CPU bursts (tau " << processes[i].getCPUTime() << ")" << std::endl; 
	
	}
	int t = -1; //int to count up time
	std::cout << "time 0ms: Simulator started for SJF [Q <empty>]"  << std::endl; 	
	while(t++) { //time loop
		if(inCS > 0) inCS--;	
		addProcesses("sjf", t, processes, queue, usingCPU);	
		if(inCS == 0) {
			startCPU(t, queue, usingCPU);	
		}
		finishCPU(t, alpha, usingCPU, queue, inIO);
		finishIO("sjf", inIO, queue, usingCPU, t);
		//check if finished here
	}
}

void srt(double alpha) {

}
