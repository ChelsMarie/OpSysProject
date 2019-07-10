#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <typeinfo>


double interarrivalTime (double min, double max, double sum, int iter) {

  srand48( time( NULL ) );

   /* <== make this number very large */

  for ( int i = 0 ; i < iterations ; i++ )
  {
      /* average should be 1/lambda ==> 1000 */

    double r = drand48();   /* uniform dist [0.00,1.00) -- also check out random() */
    double x = -log( r ) / lambda;  /* log() is natural log */

    /* avoid values that are far down the "long tail" of the distribution */
    if ( x > 3000 ) { i--; continue; }

    if ( i < 20 ) printf( "x is %lf\n", x );
    sum += x;
    if ( i == 0 || x < min ) { min = x; }
    if ( i == 0 || x > max ) { max = x; }
  }

  double avg = sum / iterations;

}

int main(int argc, char* argv[]) {


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
    double min;    
    double sum;    
    int iterations; 

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
    numProcesses = atoi(argv[5])
  }
  else {
    std::cerr << "ERROR: ARGV[5] is not an int" << std::endl;       
  }

  if (typeid(argv[6]).name() == "int") {
    numProcesses = atoi(argv[6])
  }
  else {
    std::cerr << "ERROR: ARGV[6] is not a double" << std::endl;       
  }

  if (typeid(argv[7]).name() == "double") {
    numProcesses = atof(argv[7])
  }
  else {
    std::cerr << "ERROR: ARGV[7] is not a double" << std::endl;       
  }

  if (typeid(argv[8]).name() == "string") {
    numProcesses = atoi(argv[8])
  }
  else {
    std::cerr << "ERROR: ARGV[8] is not a string" << std::endl;       
  }
  return EXIT_SUCCESS;
}