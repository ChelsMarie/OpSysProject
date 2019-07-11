#include <vector>

#ifndef PROCESS_H
#define PROCESS_H

class process {
	private:
        char letter;
        int arrTime;
        int numBursts;
        int cpuTime;
        int ioTime;
	std::string state; //should be "ready", "running", or "blocked"

	void setLet(char newLet);
	void setArrTime(int newArrTime);
	void setNumBursts(int newBursts);
	void setCPUTime(int newCPUTime);
	void setIOTime(int newIOTime);

	public:
	//constructors
	process();
	process(char let, int arr, int bursts, int cTime, int iTime);

	//gets
	char getLet();
	int getArr();
	int getBursts();
	int getCPUTime();
	int getIOTime();
	std::string getState();
	//sets
	void setState(std::string newState);
};

#endif
