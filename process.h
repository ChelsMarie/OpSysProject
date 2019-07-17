#include <vector>
#include <algorithm>

#ifndef PROCESS_H
#define PROCESS_H

class process {
	private:
    char letter;
    int arrTime;
    int numBursts;
	int waitTime;
	int turnAroundTime;
    std::vector<int> cpuTimes;
    std::vector<int> ioTimes;
	std::string state; //should be "ready", "running", or "blocked"
	//cpu and io timing variables
	int cpuFinTime;
	int ioFinTime;


	void setLet(char newLet);
	void setArrTime(int newArrTime);
	void setNumBursts(int newBursts);
	void setCPUTime(int newCPUTime);

	public:
	//constructors
	process();
	process(char let, int arr, int bursts, int cTime, int iTime);
	process(const process &p2);


	//operators
	bool operator< (const process& p);

	//gets
	char getLet() const;
	int getArr() const;
	int getBursts() const;
	int getCPUTime() const;
	int getIOTime() const;
	std::string getState() const;
	int getCPUFinTime() const;
	int getIOFinTime() const;
	//sets
	void setCPUTimes(std::vector<int> burstTimes);
	void addCPUTime(int newTime);
	void addIOTime(int newTime);
	void setState(std::string newState); //should be "ready", "running", or "blocking"
	void setCPUFinTime(int newTime);
	void setIOFinTime(int newTime);
};

#endif
