#include "process.h"

class process {

	private:
	
	char letter;
	int arrTime;
	int numBursts;
	int cpuTime;
	int ioTime;

	public:
	char getLet();
	int getArr();
	int getBursts();
	int getCPUTime();
	int getIOTime();
	

};

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
