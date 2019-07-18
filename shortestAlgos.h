#include <vector>
#include "process.h"

void checkPreempt(process * usingCPU, std::vector<process> &queue, int t);

std::string preempt(process * usingCPU, std::vector<process> &prev, std::vector<process> &queue, \
 int spot, int tl);

void termProcess(process p, int t, std::vector<process> queue);

void finishIO(std::string alg, std::vector<process> &inIO, std::vector<process> &queue, \
 process * usingCPU, int t);

void recalcTau(std::vector<process> &queue, std::vector<process> &inIO, \
 std::vector<process>::iterator &it, int t, double alpha); 

void addProcesses(std::string alg, int t, std::vector<process> &NIQ, std::vector<process> &queue, \
 process * usingCPU);

process * startCPU(int t, std::vector<process> &queue, process * usingCPU);


void sjf(double alpha, std::vector<process> processes, int cs);
