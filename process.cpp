#include <string>
#include "process.h"

//constructors
process::process() {}

process::process(char let, int arr, int bursts, int cTime, int iTime){
	setLet(let);
	setArrTime(arr);
	setNumBursts(bursts);
	setIOTime(iTime);
	setCPUTime(cTime);
	setState("ready");	
}


//gets
char process::getLet() {
	return(this -> letter);
}

int process::getArr() {
	return(this -> arrTime);
}

int process::getBursts() {
	return(this -> numBursts);
}

int process::getCPUTime() {
	return(this -> cpuTime);
}

int process::getIOTime() {
	return(this -> ioTime);
}

std::string process::getState() {
	return(this -> state);
}

//sets
void process::setState(std::string newState) {
	this -> state == newState;
} 

void process::setLet(char newLet) {
	this -> letter = newLet;
}

void process::setNumBursts(int newBursts) {
	this -> arrTime = newBursts;
}

void process::setCPUTime(int newCPUTime) {
	this -> cpuTime = newCPUTime;
}

void process::setIOTime(int newIOTime) {
	this -> ioTime = newIOTime;
}
