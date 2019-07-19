//Project by Chelsea Bovell (bovelc) and George Tate (tateg)
//TODO: edit placement var

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <typeinfo>
#include "process.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>
#include "shortestAlgos.h"

//print ready queue
void printQueue (std::vector<process> &queue) {
  for (uint i = 0; i < queue.size(); i++) {
    std::cout << " " << queue[i].getLet();
  }
}

//sorting algo for breaking ties
bool sortProcesses (const process& p1, const process& p2) {
  if (p1.getArr() != p2.getArr()) {
    return p1.getArr() < p2.getArr();
  }
  else{
    if (p1.getCPUTime() != p2.getCPUTime()) {
      return p1.getCPUTime() < p2.getCPUTime();
    }
    else {
      if (p1.getIOTime() != p2.getIOTime()) {
        return p1.getIOTime() < p2.getIOTime();
      }
      else {
        return p1.getLet() < p2.getLet();
      }
    }
  }
}

void preemptionCheck(std::vector<process> &q, std::vector<process> &qReady, int cS, int timeSlice, std::string placement,int numPreemptions, int t) {
    numPreemptions++;

    std::vector<process> qReadyPushFront;


    if (q[0].getCPUFinTime() > t + timeSlice) {
        if (qReady.size() != 0) {
            cS++;
        }

        //increment waittime
        qReady[0].incrememntWaitTime();

        if (placement == "beginning") {
            qReadyPushFront.push_back(q[0]);
            for(uint i = 0; i < qReady.size(); i++) {
                qReadyPushFront.push_back(qReady[i]); //push back elements of qReady to qReadyPushFront
            }
            qReady = qReadyPushFront; //set qReady = to new vector with element at beginning
        }

        else {
        qReady.push_back(q[0]);
        }
        q.clear();

        std::cout << "time " << t << "ms: Time slice expired; process " << qReady[0].getLet() << " preempted with " << qReady[0].getCPUFinTime() << "ms to go [Q";
        printQueue(qReady);
        std::cout << " ]" << std::endl;
    }
}

void addToRunningQueue(std::vector<process> &q, std::vector<process> &qReady, int t) {

    if (q.size() == 0 && qReady.size() > 0) {
        q.push_back(qReady[0]);
        //std::cout << "size of running after push back to it " << qReady.size() << std::endl;
        q[0].setCPUFinTime(t);
        std::cout << "time " << t << "ms: Process " << q[0].getLet() << " started using the CPU for " << q[0].getCPUTime() << "ms burst [Q";
        printQueue(qReady);
        std::cout << "]" << std::endl;
        std::cout << q[0].getLet() << " is the process not found in checkCPUFinish qRunning" << std::endl;
        qReady.erase(qReady.begin());
    }
}

void checkCPUFinish(std::vector<process> &q, std::vector<process> &qReady, int cS, int timeSlice, std::string placement, int numPreemptions, int t) {

    // if (q[0].getCPUFinTime() == t && q.size() == 1) {
          //std::cout << "time " << t << "ms: Process " << q[0].getLet() << " completed a CPU burst; " << q[0].getBursts() << " bursts to go [Q";
          //printQueue(qReady);
          //std::cout << "]" << std::endl;
                 //std::cout << q[0].getLet() << " is the process not found in checkCPUFinish qRunning" << std::endl;
                 std::cout << "gets to 2nd func " << q[0].getArr() << std::endl;
          // q[0].removeCPUTime();
          // q.clear();
          // cS++;
    // }
    // else {

    //    // preemptionCheck(q,qReady,cS,timeSlice,placement,numPreemptions,t);
   //  }
}



//check to see if the process has any more CPU bursts and if not it's completely done
//if it does, add it to the blocked queue
void checkBurstsLeft(std::vector<process> &q, std::vector<process> &qReady, std::vector<process> &qBlocked, std::vector<process> &qDone, int t) {
    if (q[0].getBursts() != 0) {
        q[0].setIOFinTime(t);
        q[0].setState("blocked");
        qBlocked.push_back(q[0]);
        q.clear();
        std::cout << "time " << t << "ms: Process " << qBlocked[0].getLet() << " switching out of CPU; will block on I/O until time " << qBlocked[0].getIOFinTime() << "ms [Q";
        printQueue(qReady);
        std::cout << "]" << std::endl;
    }

    else {
        std::cout << "time " << t << "ms: Process " << q[0].getLet() << " terminated [Q";
        printQueue(qReady);
        std::cout << "]" << std::endl;

        qDone.push_back(q[0]);
        q.clear();
    }
}

void checkIOFinish(std::vector<process> &q, std::vector<process> &qReady, std::vector<process> &qBlocked, int t) {
    if (q[0].getIOFinTime() == t) {
        q[0].removeIOTime();
        q[0].setState("ready");
        qReady.push_back(qBlocked[0]);
        q.clear();

        //increment waittime
        qReady[0].incrememntWaitTime();

        std::cout << "time " << t << "ms: Process " << q[0].getLet() << " completed I/O; added to ready queue [Q";
        printQueue(qReady);
        std::cout << "]" << std::endl;
    }

}

void RR(uint numProc, std::vector<process> &procs, int timeContextSwitch, int timeslice, std::string position, std::ofstream &outfile) {

int numPre = 0;
int totalBursts = 0;
int numContextSwitches = 0;

 std::vector<process> queueBlocked;
 std::vector<process> queueReady;
 std::vector<process> queueRunning;
 std::vector<process> queueDone; //when all cpu bursts are done, process goes here
 std::vector<int> CPUTimes;

std::sort(procs.begin(),procs.end(),sortProcesses);

//preliminarily print all procs and their arrival times and CPU burst
 for (uint i = 0; i < numProc; i++) {
    totalBursts += procs[i].getBursts();
    CPUTimes = procs[i].getAllCPUTimes();
    std::cout << "Process " << procs[i].getLet() << "[NEW] (arrival time " << procs[i].getArr() << " ms) " << procs[i].getBursts() << " CPU bursts" << std::endl;
 }


int time = 0;

std::cout << "time 0ms: Simulator started for RR [Q";
printQueue(queueReady);
std::cout << "]" << std::endl;



while (time <= 100) {
//prelim adding to readyqueue and showing cpu start burst
      for  (uint i = 0; i < procs.size(); i++) {
        if (time == procs[i].getArr())  {
          queueReady.push_back(procs[i]);
          
          procs[i].setState("ready");
          std::cout << "time " << time << "ms: Process " << procs[i].getLet() << " arrived; added to ready queue [Q";
          printQueue(queueReady);
          std::cout << "]" << std::endl;
        }
        else {
          time++;
        }
          // addToRunningQueue(queueRunning,queueReady,time);
      }
        addToRunningQueue(queueRunning,queueReady,time);
        checkCPUFinish(queueRunning,queueReady,numContextSwitches,0,"",0,time);
         //checkIOFinish(queueRunning,queueReady,queueBlocked,time);
         //checkBurstsLeft(queueRunning,queueReady,queueBlocked,queueDone,time);

        if (queueDone.size() == numProc) {
            break;
        }
        time++;
} //end of while



std::cout << "time " <<  time << "ms: Simulator ended for RR [Q";
printQueue(queueReady);
std::cout << "]" << std::endl;



 int totalCPUTimes;   
 int totalWaitTimes; 
//calculate wait time total
for (uint i = 0; i < numProc; i++) {
    totalWaitTimes = procs[i].getTotalWaitTime();
    totalCPUTimes += CPUTimes[i];
}

 double avgCPUBurstTime = (double)totalCPUTimes / (double)totalBursts;
 double avgWaitTime = (double)totalWaitTimes / (double)totalBursts;
 double avgTurnaroundTime = ((double)totalWaitTimes + (double)totalCPUTimes + (double)numContextSwitches) / (double)totalBursts; 


outfile << "Algorithm RR\n";
outfile << "-- average CPU burst time: " << std::floor(((avgCPUBurstTime * 1000) + 0.5) / 1000)  << " ms\n";;
outfile << "-- average wait time: " << std::floor(((avgWaitTime * 1000) + 0.5) / 1000) << " ms\n";
outfile << "-- average turnaround time: " << std::floor(((avgTurnaroundTime * 1000) + 0.5) / 1000) << " ms\n";
outfile << "-- total number of context switches: " << numContextSwitches << "\n";
outfile << "-- total number of preemptions: " << numPre << "\n";

} //end of RR


void FCFS(uint numProc, std::vector<process> &procs, int tCS, std::ofstream& outfile) {

 std::vector<process> queueBlocked;
 std::vector<process> queueReady;
 std::vector<process> queueRunning;
 std::vector<process> queueDone; //when all cpu bursts are done, process goes here
 std::vector<int> CPUTimes;


 int numContextSwitches = 0;
 int totalBursts = 0;


std::sort(procs.begin(),procs.end(),sortProcesses);

//preliminarily print all procs and their arrival times and CPU burst
 for (uint i = 0; i < numProc; i++) {
    totalBursts += procs[i].getBursts();
    CPUTimes = procs[i].getAllCPUTimes();
    std::cout << "Process " << procs[i].getLet() << "[NEW] (arrival time " << procs[i].getArr() << " ms) " << procs[i].getBursts() << " CPU bursts" << std::endl;
 }

int time = 0;

std::cout << "time 0ms: Simulator started for FCFS [Q";
printQueue(queueReady);
std::cout << "]" << std::endl;


while (time <= 100) {


        //prelim adding to readyqueue and showing cpu start burst
        for  (uint i = 0; i < procs.size(); i++) {

          if (time == procs[i].getArr())  {

            queueReady.push_back(procs[i]);

            procs[i].setState("ready");
            std::cout << "time " << time << "ms: Process " << procs[i].getLet() << " arrived; added to ready queue [Q";
            printQueue(queueReady);
            std::cout << "]" << std::endl;
          }
        }

        addToRunningQueue(queueRunning,queueReady,time);
        std::cout << "RunningQ[0] has " << queueRunning[0].getLet() << std::endl;
        checkCPUFinish(queueRunning,queueReady,numContextSwitches,0,"",0,time);
        // checkIOFinish(queueRunning,queueReady,queueBlocked,time);
        // checkBurstsLeft(queueRunning,queueReady,queueBlocked,queueDone,time);

        if (queueDone.size() == numProc) {
            break;
        }

        time++;
} //end of while



std::cout << "time " <<  time << "ms: Simulator ended for FCFS [Q";
printQueue(queueReady);
std::cout << "]" << std::endl;


int totalCPUTimes;   
int totalWaitTimes; 
//calculate wait time total
for (uint i = 0; i < numProc; i++) {
    totalWaitTimes = procs[i].getTotalWaitTime();
    totalCPUTimes += CPUTimes[i];
}

 double avgCPUBurstTime = (double)totalCPUTimes / (double)totalBursts;
 double avgWaitTime = (double)totalWaitTimes / (double)totalBursts;
 double avgTurnaroundTime = ((double)totalWaitTimes + (double)totalCPUTimes + (double)numContextSwitches) / (double)totalBursts; 



outfile << "Algorithm FCFS\n";
outfile << "-- average CPU burst time: " << std::floor(((avgCPUBurstTime * 1000) + 0.5) / 1000)  << " ms\n";;
outfile << "-- average wait time: " << std::floor(((avgWaitTime * 1000) + 0.5) / 1000) << " ms\n";
outfile << "-- average turnaround time: " << std::floor(((avgTurnaroundTime * 1000) + 0.5) / 1000) << " ms\n";
outfile << "-- total number of context switches: " << numContextSwitches << "\n";
outfile << "-- total number of preemptions: 0\n";

} //end of FCFS

int main(int argc, char* argv[]) {

  setvbuf( stdout, NULL, _IONBF, 0 );

  //ERROR CHECING
  if (argc != 8 && argc != 9) {
    std::cerr << "ERROR: You need 8 or 9 arguments." << std::endl;
    return(EXIT_FAILURE);
  }

  int seed; //argv[1] 
  double lambda; //argv[2] 
  int max;     //argv[3]     
  int numProcesses; //argv[4]
  int tCS; //argv[5]
  double alpha; //argv[6]
  int timeSlice; //argv[7]
  std::string rrAdd = "END"; //argv[8]


  seed = atoi(argv[1]);
  lambda = atof(argv[2]);
  max = atoi(argv[3]);
  numProcesses = atoi(argv[4]);
  tCS = atoi(argv[5]);
  alpha  = atof(argv[6]);
  timeSlice = atoi(argv[7]);

  if (argc == 9) {
      rrAdd = (std::string) argv[8];
  }


  std::vector<process> processes;
  std::string alphabetLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  //does stackdump file error with everything else commented out
  //do interarrival times
  srand48( seed );

  for ( int i = 0 ; i < numProcesses ; i++ ) {

    process proc;

    double r = drand48();   /* uniform dist [0.00,1.00) -- also check out random() */
    double x = -log( r ) / lambda;  /* log() is natural log */

    /* avoid values that are far down the "long tail" of the distribution */
    if ( x > max ) { i--; continue; }

    //set letters to correspond with proc ID
    proc.setLet(alphabetLetters.at(i));

    proc.setArrTime(floor(x));
    
    r = drand48();
    int bursts = (r*100)+1;
    //std::cout << "Bursts: " << bursts << std::endl;
    proc.setNumBursts(bursts);   

    proc.setInitialTau((int)1/lambda);

    for (int j = 0; j < proc.getBursts(); j++) {
      r = drand48();
      x = -log( r ) / lambda;
      proc.addCPUTime((int)ceil(x));

      if(j < proc.getBursts()-1) {
        r = drand48();
        x = -log( r ) / lambda;
	     proc.addIOTime(ceil(x));
      }
    }

    proc.setLastTime(proc.getCPUTime());
    processes.push_back(proc);
 }

    std::ofstream outputFile("simout.txt");

    //FCFS (numProcesses,processes,tCS,outputFile);
    //RR (numProcesses,processes,tCS,timeSlice,rrAdd,outputFile);
    sjf(alpha, processes, tCS);
    srt(alpha, processes, tCS);
    outputFile.close();


  return EXIT_SUCCESS;
}
/*
  if (typeid(argv[1]).name() == "int") {
    seed = atoi(argv[1]);
  }
  else {
    std::cerr << "ERROR: ARGV[1] is not an int" << std::endl;
  }

  if (typeid(argv[2]).name() == "double") {
    lambda = atof(argv[2]);
  }
  else {
    std::cerr << "ERROR: ARGV[2] is not a double" << std::endl;   
  }

  if (typeid(argv[3]).name() == "double") {
    max = atof(argv[3]);
  }
  else {
    std::cerr << "ERROR: ARGV[3] is not a double" << std::endl;   
  }

  if (typeid(argv[4]).name() == "int") {
    numProcesses = atoi(argv[4]);
  }
  else {
    std::cerr << "ERROR: ARGV[4] is not an int" << std::endl;       
  }

  if (typeid(argv[5]).name() == "int") {
    tCS = atoi(argv[5]);
  }
  else {
    std::cerr << "ERROR: ARGV[5] is not an int" << std::endl;       
  }

  if (typeid(argv[6]).name() == "int") {
    alpha = atoi(argv[6]);
  }
  else {
    std::cerr << "ERROR: ARGV[6] is not a double" << std::endl;       
  }

  if (typeid(argv[7]).name() == "double") {
    timeSlice = atof(argv[7]);
  }
  else {
    std::cerr << "ERROR: ARGV[7] is not a double" << std::endl;       
  }

  if (typeid(argv[8]).name() == "string") {
    rrAdd = atoi(argv[8]);
  }
  else {
    std::cerr << "ERROR: ARGV[8] is not a string" << std::endl;       
  }
*/



    /*
    ????
    After you simulate each scheduling algorithm, you must reset the simulation back to the initial
    set of processes and set your elapsed time back to zero. More specifically, you must re-seed your
    random number generator to ensure the same set of processes and interarrival times.
    */
