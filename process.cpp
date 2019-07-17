#include <string>
#include <algorithm>
#include "process.h"

//constructors
process::process() {}

process::process(char let, int arr, int bursts, int cTime, int iTime){
	numBursts = cpuTimes.size();
	setLet(let);
	setArrTime(arr);
	setNumBursts(bursts);
	//setIOTime(iTime);
	//setCPUTime(cTime);
	setState("ready");
	setCPUFinTime(-1);
	setIOFinTime(-1);	
}

process::process(const process &p2){

	/*
	setLet(p2.getLet());
	setArrTime(p2.getArr());
	setNumBursts(p2.getBursts());
	*/
	letter = p2.letter;
	arrTime = p2.arrTime;
	numBursts = p2.numBursts;
	waitTime = p2.waitTime;
	turnAroundTime = p2.turnAroundTime;
	cpuTimes = p2.cpuTimes;
	ioTimes = p2.ioTimes;
	state = p2.state;
	cpuFinTime = p2.cpuFinTime;
	ioFinTime = p2.ioFinTime;
			

}



//operators/compare functions

//compares the next cpu times for each process
bool process::operator< (const process& p) { 
	return(this -> getCPUTime() < p.getCPUTime());
}


//gets
char process::getLet() const{
	return(this -> letter);
}

int process::getArr() const{
	return(this -> arrTime);
}

int process::getBursts() const{
	return(this -> cpuTimes.size());
}

int process::getCPUTime() const{
	return(this -> cpuTimes[0]);
}

int process::getIOTime() const{
	return(this -> ioTimes[0]);
}

std::string process::getState() const{
	return(this -> state);
}

int process::getCPUFinTime() const{
	return(this -> cpuFinTime);
}

int process::getIOFinTime() const{
	return(this -> ioFinTime);
}

//sets
void process::setState(std::string newState) {
	this -> state == newState;
} 

void process::setLet(char newLet) {
	this -> letter = newLet;
}

void process::setNumBursts(int newBursts) {
	this -> numBursts = newBursts;
}

void process::setCPUTimes(std::vector<int> burstTimes){
	this -> cpuTimes.clear();		
	for(int i = 0; i < this -> numBursts; i++) {
		this -> cpuTimes.push_back(burstTimes[i]);
	}
}

void process::addCPUTime(int newTime) { //adds new time to the end of the process
	this -> cpuTimes.push_back(newTime);
}

void process::removeCPUTime() {
	cpuTimes.erase(cpuTimes.begin());
}

void process::addIOTime(int newTime) {
	this -> ioTimes.push_back(newTime);
}
void process::setCPUFinTime(int newTime) {
	this -> cpuFinTime = newTime;
}

void process::setIOFinTime(int newTime) {
	this -> ioFinTime = newTime;
}
/*
void process::setCPUTime(int newCPUTime) {
	this -> cpuTime = newCPUTime;
}

void process::setIOTime(int newIOTime) {
	this -> ioTime = newIOTime;
}
*/
