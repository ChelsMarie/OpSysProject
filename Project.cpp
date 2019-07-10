#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

float interarrivalTime (float min, float max, float sum, int iter) {

  srand48( time( NULL ) );

   /* <== make this number very large */

  for ( int i = 0 ; i < iterations ; i++ )
  {
      /* average should be 1/lambda ==> 1000 */

    float r = drand48();   /* uniform dist [0.00,1.00) -- also check out random() */
    float x = -log( r ) / lambda;  /* log() is natural log */

    /* avoid values that are far down the "long tail" of the distribution */
    if ( x > 3000 ) { i--; continue; }

    if ( i < 20 ) printf( "x is %lf\n", x );
    sum += x;
    if ( i == 0 || x < min ) { min = x; }
    if ( i == 0 || x > max ) { max = x; }
  }

  float avg = sum / iterations;

}

int main(int argc, char* argv[]) {


	//ERROR CHECING
	if (argc != 9) {
		std::cerr << "ERROR: You need 9 arguments." << std::endl;
	}


 	int seed; //argv[1] 
 	float lambda; //argv[2] 
 	float max;     //argv[3]     
  	int numProcesses; //argv[4]
  	int tCS; //argv[5]
  	double alpha; //argv[6]
  	float min;    
    float sum;    
  	int iterations; 

  
}