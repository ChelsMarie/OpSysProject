#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <typeinfo>
#include <process.h>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <vector>
#include <fstream>

//print ready queue
void printQueue (std::vector<process> queue) {
  for (int i = 0; i < queue.size(); i++) {
    std::cout << " " << queue[i].getLet();
  }
}

//sorting algo for breaking ties
bool sortProcesses() (const process& p1, const process& p2) {
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

void addToRunningQueue(std::vector<process> q, std::vector<process> qReady) {
    if (q.size() == 0) {
        q.push_back(qReady[0]);
        qReady.erase(qReady[0]);
        t = high_resolution_clock::now();
        q[i].setCPUFinTime(t+q[i].getCPUTime());
        std::cout << "time " << t << "ms: Process " << q[0].getLet() << " started using the CPU for " << q[i].getCPUTime() << "ms burst [Q " << printQueue(qReady) >> "]" << std::endl;
        q[0].setState("running");
  }
  else {
    continue;
  }
}

void checkCPUFinish(std::vector<process> q, std::vector<process> qReady) {
    t = high_resolution_clock::now();     
    if (q[0].getCPUFinTime() == t) {
          q[0].removeCPUTime();
          t = high_resolution_clock::now();   
          std::cout << "time " << t << " << ms: Process " << q[i].getLet() << " completed a CPU burst; " << q[i].getBursts() << " bursts to go [Q " << printQueue(qReady) << "]" << std::endl;
    }
    else {
        continue;
    }
}

//check to see if the process has any more CPU bursts and if not it's completely done
//if it does, add it to the blocked queue
void checkBurstsLeft(std::vector<process> q, std::vector<process> qReady, std::vector<process> qBlocked) {
    if (q[0].getBursts() != 0) {
        t = high_resolution_clock::now();   
        q[0].setIOFinTime(t+q[0].getIOTime());
        q[0].setState("blocked");
        qBlocked.push_back(q.pop());
        t = high_resolution_clock::now();   
        std::cout << "time " << t << "ms: Process " << qBlocked[0].getLet() << " switching out of CPU; will block on I/O until time " << qBlocked.getIOTime() << "ms [Q " << printQueue(qReady) << "]" << std::endl;
    }

    else {
        t = high_resolution_clock::now();   
        std::endl << "time " << t << "ms: Process " << q[0].getLet() << " terminated [Q " << printQueue(qReady) << "]" std::endl;
        queueDone.push_back(q.pop());
    }
}

void checkIOFinish(std::vector<process> q, std::vector<process> qReady, std::vector<process> qBlocked) {
    if (q[0].getIOFinTime() == t) {
        q[0].removeIOTime();
        q[0].setState("ready");
        q.push_back(qBlocked.pop());
        t = high_resolution_clock::now();   
        std::cout << "time " << t << "ms: Process " << q[0].getLet() << " completed I/O; added to ready queue [Q " << printQueue(qReady) << "]" << std::endl;
    }

    else {
        continue;
    }
}

void RR(int numProc,std::vector<process> procs, int timeContextSwitch, int timeslice, std::string position) {
     std::vector<process> queueBlocked;
 std::vector<process> queueReady;
 std::vector<process> queueRunning;
 std::vector<process> queueDone; //when all cpu bursts are done, process goes here

std::sort(procs.begin(),procs.end(),sortProcesses);

//preliminarily print all procs and their arrival times and CPU burst
 for (int i = 0; i < numProc; i++) {
  std::out << "Process " << procs[i].getLet() << "[NEW] (arrival time " << procs[i].getArr() << " ms) " << procs[i].getBursts() << " CPU bursts" << std::endl;
 }


std::chrono::high_resolution_clock::time_point t = 0;

std::cout << "time 0ms: Simulator started for FCFS [Q " << printQueue(queueReady) << "]" << std::endl;

//prelim adding to readyqueue and showing cpu startburst
for  (int i = 0; i < procs.size(); i++) {
  t = high_resolution_clock::now();
  if (t == procs[i].arrTime())  {
    queueReady.push_back(procs[i]);
    procs[i].setState("ready");
    std::cout << "time " << t << "ms: Process " << procs[i].getLet() << " arrived; added to ready queue [Q" << printQueue(queueReady) << "]" << std::endl;
  }
    addToRunningQueue(queueRunning,queueReady);
}

while (queueDone.size() != numProcesses) {
        t = high_resolution_clock::now();   

        addToRunningQueue(queueRunning,queueReady);
        checkCPUFinish(queueRunning,queueReady);
        checkIOFinish(queueRunning,queueReady,queueBlocked);
        checkBurstsLeft(queueRunning,queueReady,queueBlocked);

        if (queueDone.size() == numProcesses) {
            break;
        }
} //end of while

    t = high_resolution_clock::now();   
    std::cout << "time " << t << "ms: Simulator ended for FCFS [Q " << printQueue(queueReady) << "]" << std::endl;


}

void FCFS(int numProc, std::vector<process> procs, int tCS) {

 std::vector<process> queueBlocked;
 std::vector<process> queueReady;
 std::vector<process> queueRunning;
 std::vector<process> queueDone; //when all cpu bursts are done, process goes here

std::sort(procs.begin(),procs.end(),sortProcesses);

//preliminarily print all procs and their arrival times and CPU burst
 for (int i = 0; i < numProc; i++) {
  std::out << "Process " << procs[i].getLet() << "[NEW] (arrival time " << procs[i].getArr() << " ms) " << procs[i].getBursts() << " CPU bursts" << std::endl;
 }


std::chrono::high_resolution_clock::time_point t = 0;

std::cout << "time 0ms: Simulator started for FCFS [Q " << printQueue(queueReady) << "]" << std::endl;

//prelim adding to readyqueue and showing cpu startburst
for  (int i = 0; i < procs.size(); i++) {
  t = high_resolution_clock::now();
  if (t == procs[i].arrTime())  {
    queueReady.push_back(procs[i]);
    procs[i].setState("ready");
    std::cout << "time " << t << "ms: Process " << procs[i].getLet() << " arrived; added to ready queue [Q" << printQueue(queueReady) << "]" << std::endl;
  }
    addToRunningQueue(queueRunning,queueReady);
}

while (queueDone.size() != numProcesses) {
        t = high_resolution_clock::now();   

        addToRunningQueue(queueRunning,queueReady);
        checkCPUFinish(queueRunning,queueReady);
        checkIOFinish(queueRunning,queueReady,queueBlocked);
        checkBurstsLeft(queueRunning,queueReady,queueBlocked);

        if (queueDone.size() == numProcesses) {
            break;
        }
} //end of while

    t = high_resolution_clock::now();   
    std::cout << "time " << t << "ms: Simulator ended for FCFS [Q " << printQueue(queueReady) << "]" << std::endl;


} //end of FCFS

int main(int argc, char* argv[]) {

  setvbuf( stdout, NULL, _IONBF, 0 );

  //ERROR CHECING
  if (argc != 9) {
    std::cerr << "ERROR: You need 9 arguments." << std::endl;
  }


  int seed; //argv[1] 
  double lambda; //argv[2] 
  double max;     //argv[3]     
  int numProcesses; //argv[4]
  int tCS; //argv[5]
  double alpha; //argv[6]
  double timeSlice; //argv[7]
  std::string rrAdd = "END"; //argv[8]

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
    numProcesses = atoi(argv[4])
  }
  else {
    std::cerr << "ERROR: ARGV[4] is not an int" << std::endl;       
  }

  if (typeid(argv[5]).name() == "int") {
    tCS = atoi(argv[5])
  }
  else {
    std::cerr << "ERROR: ARGV[5] is not an int" << std::endl;       
  }

  if (typeid(argv[6]).name() == "int") {
    alpha = atoi(argv[6])
  }
  else {
    std::cerr << "ERROR: ARGV[6] is not a double" << std::endl;       
  }

  if (typeid(argv[7]).name() == "double") {
    timeSlice = atof(argv[7])
  }
  else {
    std::cerr << "ERROR: ARGV[7] is not a double" << std::endl;       
  }

  if (typeid(argv[8]).name() == "string") {
    rrAdd = atoi(argv[8])
  }
  else {
    std::cerr << "ERROR: ARGV[8] is not a string" << std::endl;       
  }


  std::vector<process> processes;
  std::string alphabetLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  //do interarrival times
  srand48( time( NULL ) );
  double sum;

  for ( int i = 0 ; i < numProcesses ; i++ )
  {

    process proc;

    double r = drand48();   /* uniform dist [0.00,1.00) -- also check out random() */
    double rNext = drand48();
    double x = -log( r ) / lambda;  /* log() is natural log */

    //set letters to correspond with proc ID
    proc.setLet(alphabetLetters.at(i));

    if (i == 0) {
      proc.setArrTime(floor(r));
      proc.setNumBursts((r*100)+1);   
    }

    for (int j = 0; j < proc.getBursts(); j++) {
      proc.addCPUTime(ceil(r));
      proc.addIOTime(ceil(rNext));
    }

    processes.push_back(proc);
    /* avoid values that are far down the "long tail" of the distribution */
    if ( x > max ) { i--; continue; }

    sum += x;
    if ( i == 0 || x < min ) { min = x; }
    if ( i == 0 || x > max ) { max = x; }
  }

  double avg = sum / numProcesses;


FCFS (numProcesses,processes,tCS);
RR (numProcesses,processes, tCS, timeSlice, rrAdd);

ofstream outFile("simout.txt");
outFIle.close();



  return EXIT_SUCCESS;
}