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
	std::string state;


	public:
	char getLet();
	int getArr();
	int getBursts();
	int getCPUTime();
	int getIOTime();
	std::string getState();
};

#endif
