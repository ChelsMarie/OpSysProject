#include <vector>
#include <algorithm>
#include <chrono>

#ifndef PROCESS_H
#define PROCESS_H

class process {
	private:
        char letter;
	int tau;
	int arrTime;
        int numBursts;
	int waitTime;
	int turnAroundTime;
        std::vector<int> cpuTimes;
        std::vector<int> ioTimes;
    
    char letter;
    int arrTime;
    int numBursts;
	std::chrono::high_resolution_clock::time_point beginWait;
	std::chrono::high_resolution_clock::time_point endWait;
	std::chrono::high_resolution_clock::time_point waitTimeTotal;
	std::chrono::high_resolution_clock::time_point turnAroundTime;
    std::vector<int> cpuTimes;
    std::vector<int> ioTimes;
    std::vector<std::chrono::high_resolution_clock::time_point> waitTimes;
	
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
	int getCPUFinTime() const;
	int getIOFinTime() const;
	
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



	std::chrono::high_resolution_clock::time_point getTurnaroundTime() const;
	std::chrono::high_resolution_clock::time_point getBeginWait() const; 
	std::chrono::high_resolution_clock::time_point getEndWait() const; 

	//sets
	void setCPUTimes(std::vector<int> burstTimes);
	void setturnAroundTime(std::chrono::high_resolution_clock::time_point newTime);
	void setBeginWait(std::chrono::high_resolution_clock::time_point newTime);
	void setEndWait(std::chrono::high_resolution_clock::time_point newTime);
	void addCPUTime(int newTime);
	void removeCPUTime();
	void removeIOTime()
	void addIOTime(int newTime);
	void setState(std::string newState); //should be "ready", "running", or "blocking"
	void setCPUFinTime(int newTime);
	void setIOFinTime(int newTime);
	void addWaitTime(int newTime);
};

bool letSort(const process& p1, const process& p2);

#endif
