//Project by Chelsea Bovell (bovelc) and George Tate (tateg)

#include <vector>
#include <algorithm>
#include <chrono>

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
	int tau;

	public:
	//constructors
	process();
	process(char let, int arr, int bursts, int cTime, int iTime);
	process(const process &p2);
	process(const int finTime); //dummy constructor ONLY FOR WAITING ON CONTEXT SWITCH


	//operators
	bool operator<  (const process& p); //compares next burst time
	bool operator== (const process& p); //returns true if the processes have the same letter

	//gets
	char getLet() const;
	int getArr() const;
	int getBursts() const;
	int getCPUTime() const;
	int getIOTime() const;
	std::string getState() const;
	std::vector<int> getAllCPUTimes();
	int getCPUFinTime() const;
	int getIOFinTime() const;
	int getTurnaroundTime() const;
	int getTotalWaitTime() const;
	int getTau() const;


	//sets
	void setCPUTimes(std::vector<int> burstTimes);
	void insertCPUTime(int newTime);
	void addCPUTime(int newTime);
	void addIOTime(int newTime);
	void setState(std::string newState); //should be "ready", "running", or "blocking"
	void setCPUFinTime(int currentTime);
	void setInitialTau(int tau);
	void setNewTau(double alpha, int t);
	void setIOFinTime(int currentTime);

	void setLet(char newLet);
	void setArrTime(int newArrTime);
	void setNumBursts(int newBursts);
	void setCPUTime(int newCPUTime);
	void setIOTime(int newIOTime);
	void incrememntWaitTime();
	void removeCPUTime();
	void removeIOTime();

};

bool letSort(const process& p1, const process& p2);

#endif
