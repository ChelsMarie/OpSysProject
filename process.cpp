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
	waitTime = 0;
	turnAroundTime = 0;
	//setIOTime(iTime);
	//setCPUTime(cTime);
	setState("ready");
	//setCPUFinTime(-1);
	//setIOFinTime(-1);	
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
	tau = p2.tau;
	state = p2.state;
	cpuFinTime = p2.cpuFinTime;
	ioFinTime = p2.ioFinTime;
			

}



//operators/compare functions

//compares the next cpu times for each process
bool process::operator< (const process& p) { 
	return(this -> getCPUTime() < p.getCPUTime());
}

bool process::operator== (const process& p) {
	return(this -> getLet() == p.getLet());
}

bool letSort(const process& p1, const process& p2) {
	return(p2. getLet() < p1.getLet());
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
	return(cpuFinTime);
}

int process::getIOFinTime() const{
	return(this -> ioFinTime);
}

int process::getTau() const {
	return(this -> tau);

std::chrono::high_resolution_clock::time_point process::getTurnaroundTime() const {
	return (this -> turnAroundTime);
}
std::chrono::high_resolution_clock::time_point process::getBeginWait() const {
	return (this -> beginWait);
}
std::chrono::high_resolution_clock::time_point process::getEndWait() const {
	return (this -> endWait);
}

//sets
void process::setState(std::string newState) {
	this -> state = newState;
} 

void process::setturnAroundTime(std::chrono::high_resolution_clock::time_point newTime) {
	this -> turnAroundTime = newTime;
}
void process::setBeginWait(std::chrono::high_resolution_clock::time_point newTime) {
	this -> waitTime = newTime;
}
void process::setEndWait(std::chrono::high_resolution_clock::time_point newTime) {
	this -> waitTime = newTime;
}
void process::setLet(char newLet) {
	this -> letter = newLet;
}

void process::setNumBursts(int newBursts) {
	this -> numBursts = newBursts;
}

void process::setArrTime(int newArrTime) {
	this -> arrTime = newArrTime;
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

void process::addIOTime(int newTime) { //adds new time to the end of the process
	this -> ioTimes.push_back(newTime);
}

/*
increment numBursts because this should only happen when a process is preempted, so the removed
 time needs to be re-added as time left
*/
void process::insertCPUTime(int newTime) { 
	this -> cpuTimes.insert(cpuTimes.begin(), newTime);
	numBursts++; 

void process::removeCPUTime() {
	cpuTimes.erase(cpuTimes.begin());
}

void process::removeIOTime() {
	ioTimes.erase(ioTimes.begin());
}

void process::addIOTime(int newTime) {
	this -> ioTimes.push_back(newTime);
}
void process::setCPUFinTime(int newTime) {
	this -> cpuFinTime = newTime;
}

void process::setCPUFinTime(int currentTime) {
	//if(numBursts == 1) {
	//	csTime/=2;
	//}
	this -> cpuFinTime = cpuTimes[0] + currentTime;
	cpuTimes.erase(cpuTimes.begin());
	numBursts--;	
}

void process::setIOFinTime(int currentTime) {
	this -> ioFinTime = currentTime + ioTimes[0];
	ioTimes.erase(ioTimes.begin());
}

void process::setInitialTau(int newTau) {
	this -> tau = newTau;
}

void process::setNewTau(double alpha, int t) {
	int oldTau = this -> tau;
	int newTau = (alpha * oldTau) + ((1-alpha) * oldTau);
	this -> tau = newTau;
}

void setturnAroundTime(std::chrono::high_resolution_clock::time_point newTime) {
	this -> turnAroundTime = newTime;
}

void setwaitTime(std::chrono::high_resolution_clock::time_point newTime) {
	this -> waitTime = newTime;
}

void process::addWaitTime(int newTime) {
	waitTimes.push_back(newTime);
}

void process::waitTimeTotalCalc() {
	for(int i = 0; i < waitTimes.size()) {
		waitTimeTotal += waitTimes[i];
	}
}
/*
void process::setCPUTime(int newCPUTime) {
	this -> cpuTime = newCPUTime;
}

void process::setIOTime(int newIOTime) {
	this -> ioTime = newIOTime;
}
*/
