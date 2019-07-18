#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <typeinfo>
#include "shortestAlgos.h"
#include "process.h"
#include <cmath>

void randomGen (int seed, double lambda, double max, process &p) {

  srand48(seed); 

  double r = drand48();  
  double x = -log( r ) / lambda; 
  int arrTime = floor(x);

  p.setArrTime(arrTime);

  r = drand48();  
  //x = -log( r ) / lambda; 
  //int bursts = (x * 100);
  int bursts = (r * 100)+1;

  p.setNumBursts(bursts);

  for ( int i = 0 ; i < (bursts * 2)-1; i++ )
  {

    r = drand48();  
    x = -log( r ) / lambda; 
    int burstTime = ceil(x);

    if ( x > max ) { i--; continue; }
    else {
      if(i%2 != 0) {
        p.addCPUTime(burstTime);
      } else {
        p.addIOTime(burstTime);
      }
    }
  }
}

int main(int argc, char* argv[]) {


  //ERROR CHECING
  if (argc != 9) {
    std::cerr << "ERROR: You need 9 arguments." << std::endl;
    return(EXIT_FAILURE);
  }


  int seed; //argv[1] 
  double lambda; //argv[2] 
  double max;     //argv[3]     
  int numProcesses; //argv[4]
  int tCS; //argv[5]
  double alpha; //argv[6]
  double timeSlice; //argv[7]
  std::string rrAdd = "END"; //argv[8]

  seed = atoi(argv[1]);
  lambda = atof(argv[2]);
  max = atof(argv[3]);
  numProcesses = atoi(argv[4]);
  tCS = atoi(argv[5]);
  alpha  = atoi(argv[6]);
  timeSlice = atof(argv[7]);
  rrAdd = atoi(argv[8]);

  #ifdef DEBUGMODE
  std::cout << "numProcces: " << numProcesses << std::endl;
  #endif
/*
   if (typeid(argv[1]).name() == "int") {
    seed = atoi(argv[1]);
  } else {
    std::cerr << "ERROR: ARGV[1] is not an int" << std::endl;
  }

  if (typeid(argv[2]).name() == "double") {
    lambda = atof(argv[2]);
  } else {
    std::cerr << "ERROR: ARGV[2] is not a double" << std::endl;   
  }

  if (typeid(argv[3]).name() == "double") {
    max = atof(argv[3]);
  } else {
    std::cerr << "ERROR: ARGV[3] is not a double" << std::endl;   
  }

  if (typeid(argv[4]).name() == "int") {
    numProcesses = atoi(argv[4]);
  } else {
    std::cerr << "ERROR: ARGV[4] is not an int" << std::endl;       
  }

  if (typeid(argv[5]).name() == "int") {
    tCS = atoi(argv[5]);
  } else {
    std::cerr << "ERROR: ARGV[5] is not an int" << std::endl;       
  }

  if (typeid(argv[6]).name() == "double") {
    alpha  = atoi(argv[6]);
  } else {
    std::cerr << "ERROR: ARGV[6] is not a double" << std::endl;       
  }

  if (typeid(argv[7]).name() == "double") {
  timeSlice   = atof(argv[7]);
  } else {
    std::cerr << "ERROR: ARGV[7] is not a double" << std::endl;       
  }

  if (typeid(argv[8]).name() == "string") {
  rrAdd   = atoi(argv[8]);
  } else {
    std::cerr << "ERROR: ARGV[8] is not a string" << std::endl;       
  }
*/
  std::vector<process> allProcesses;

  for(int i = 1; i <= numProcesses; i++) {
    process p;
    char let = i+64;
    p.setLet(let);
    p.setInitialTau(int(1/lambda));
    randomGen(seed, lambda, max, p);
    #ifdef DEBUGMODE
    std::cout << "Arr Time: " << p.getArr() << std::endl;
    std::cout << "Bursts: " << p.getBursts() << std::endl;
    std::cout << "number of IOs: " << p.get
    #endif        
    allProcesses.push_back(p);
  }

  sjf(alpha, allProcesses, tCS);


  return EXIT_SUCCESS;
}
