#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
#include "shortestAlgos.h" 
#include "process.h" 

int inCS = 0;
int csTime = 0;
int finTime = -6;

std::string getQueue(std::vector<process> queue) {
	std::string q = " [Q";
	for(uint i = 0; i < queue.size(); i++) {
		#ifdef DEBUGMODE
		std::cout << queue[i].getLet() << std::endl;
		#endif
		if(queue[i].getState() != "running") {
			q += " ";
			q += queue[i].getLet(); 
		}
	}
	if(q.size() == 3) {
		q += " <empty>";
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
	for(uint i = 0; i < queue.size(); i++) {
		if(queue[i].getCPUTime() < tl) {
			std::string message = getStart(t);
			usingCPU -> setState("ready");
			usingCPU -> insertCPUTime(tl);
			//process * oldUser = usingCPU;
			usingCPU = &queue[i];
			usingCPU -> setState("ready");		
		}
	}
}

//for preemptions that happen as the result of another event (arrival or end of IO)
std::string preempt(process * usingCPU, std::vector<process> &prev, std::vector<process> &queue, \
 int spot, int tl) {
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
	for(uint i = 0; i < inIO.size(); i++) {
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
void recalcTau(std::vector<process> &queue, std::vector<process> &inIO, \
 std::vector<process>::iterator &it, int t, double alpha) {
	it -> setNewTau(alpha, t);
	std::string message =  getStart(t);
	message += " Recalculated tau = " + std::to_string(it -> getTau()); 
	message +=  " ms for process ";
	message +=  it -> getLet(); 
	message += getQueue(queue);
	std::cout << message << std::endl;
}

void finishCPU(int t, double alpha, process * usingCPU, std::vector<process> &queue, \
 std::vector<process> &inIO) {
	std::vector<process>::iterator it;
	for(it = queue.begin(); it != queue.end(); it++) {
		if(it -> getState() == "running") break;
	}
	if(it == queue.end()) return;
	if(finTime == t) {
		//it = std::find(queue.begin(), queue.end(), *usingCPU);
		std::string message = getStart(t); 
		message += "Process ";
		message +=  it -> getLet();
		message += " (tau " + std::to_string(it -> getTau()) + ") completed a CPU burst; ";
		message += std::to_string(it -> getBursts()) + " to go" + getQueue(queue); 
		if(it != queue.end()) {
			it -> setState("blocked");	
			it -> setIOFinTime(t);
			inIO.push_back(*it);
			it = inIO.end()-1;
			queue.erase(it);
			message += "\n" + getStart(t) + "Process" + it -> getLet();
			message += " switching out of CPU; will block on I/O until time ";
			message += std::to_string(it -> getIOFinTime());
			message += getQueue(queue); 
		}
		std::cout << message << std::endl;
		recalcTau(inIO, queue, it, t, alpha);
	}
}

void addProcesses(std::string alg, int t, std::vector<process> &NIQ, std::vector<process> &queue, \
 process * usingCPU) {
	//check if any process arrive for the first time
	for(uint i = 0; i < NIQ.size(); i++) {
		if(NIQ[i].getArr() == t) { 
			std::string message = "";
			queue.push_back(NIQ[i]);	
			message += "time " + std::to_string(t) + "ms: Process " + NIQ[i].getLet(); 
			message += " (tau " + std::to_string(NIQ[i].getTau()) +  " ms) arrived;";
		
			if(alg == "srt") {
				int tl = (usingCPU -> getCPUFinTime()) - t; 	
				if(NIQ[i].getCPUTime() < tl){
					message += preempt(usingCPU, NIQ, queue, i, tl);	
				}
				else message += " added to ready queue";
			}
			else message += " added to ready queue";
			message += getQueue(queue);
			NIQ.erase(NIQ.begin()+i);
			i--; //decrement i to prevent the next process getting skipped
			//sort queue in decreasing order by next burst time
			std::cout << message << std::endl;
		}
	}
}


//check if process begins using cpu
process * startCPU(int t, std::vector<process> &queue) {
	//if nobody is using the cpu and there are things in queue
	//process * usingCPU;
	for(uint i = 0; i < queue.size(); i++) {
		if(queue[i].getState() == "running") {
			return(NULL);
		}
	}
	if(queue.size() > 0) {
		std::sort(queue.begin(), queue.end()); 
		std::string message = "";
		#ifdef DEBUGMODE
		std::cout << queue.size() <<std::endl;
		#endif
		queue[0].setState("running");
		queue[0].setCPUFinTime(t);
		finTime = queue[0].getCPUFinTime();  
		//usingCPU = &queue[0];
		message += "time: " + std::to_string(t) + " ms: Process " + queue[0].getLet();
		message += " (tau " + std::to_string(queue[0].getTau()) + ") started using";
		message += " the CPU for " + std::to_string(queue[0].getCPUTime()) + "ms burst";
		message += getQueue(queue);
		std::cout << message << std::endl;  
	}
	return(&(*queue.begin()));
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
		std::cout << "Process " << processes[i].getLet() << " [NEW] (arrival time: ";
		std::cout << processes[i].getArr() << "ms) " << processes[i].getBursts();
		std::cout << " CPU bursts (tau " << processes[i].getCPUTime() << ")" << std::endl; 
	}
	int t = -1; //int to count up time
	std::cout << "time 0ms: Simulator started for SJF [Q <empty>]"  << std::endl; 	
	while(1) { //time loop
		t++;
		#ifdef DEBUGMODE
		//std::cout << "shits going on! " << t << std::endl;
		#endif
		if(inCS > 0) inCS--;	
		addProcesses("sjf", t, processes, queue, usingCPU);	
		if(inCS == 0) {
			usingCPU = startCPU(t, queue);	
		}
		finishCPU(t, alpha, usingCPU, queue, inIO);
		finishIO("sjf", inIO, queue, usingCPU, t);
		//check if finished here
		if(queue.size() == 0 && processes.size() == 0 && inIO.size() == 0) {
			std::cout << "Done!" << std::endl;
			break;	
		}
	}
}

void srt(double alpha, std::vector<process> processes, int cs) {
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
		addProcesses("srt", t, processes, queue, usingCPU);	
		if(inCS == 0) {
			usingCPU = startCPU(t, queue);
			#ifdef DEBUGMODE
			std::cout << usingCPU -> getLet() << " is using CPU" << std::endl;	
			#endif
		}
		finishCPU(t, alpha, usingCPU, queue, inIO);
		finishIO("srt", inIO, queue, usingCPU, t);
		//check if finished here
	}
}
