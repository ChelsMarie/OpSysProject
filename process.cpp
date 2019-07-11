#include "process.h"

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
