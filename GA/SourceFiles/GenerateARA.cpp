// This function will generate one antenna for the ARA experiment and then call the constraint function

#include <time.h>
#include <math.h>
#include <random>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>

vector<vector<float> > GenerateARA(int sections, int genes)
{
  // initialize an interesect condidtion
  bool intersect = True;
  vector<vector<<float> > antenna = [][];
  
  // variables
  float max_outer_radius = 7.5;
  float max_radius = max_outer_radius;
  float min_length = 10.0; // in cm
  float max_length = 140;  // in cm
  float max_theta = atan(max_outer_radius/min_length);
  float min_A = -1.0; 
  float max_A = 1.0;
  float min_B = -1.0; 
  float max_B = 1.0;

  for(int i=0; i<sections, i++)
  {
    // while the intersect condition is true, generate the side of an individual
    while(intersect==True)
    {
      std::uniform_real_distribution <float> distribution_radius(0, max_radius);          // Inner Radius
      float R = distribution_radius(generator);
      std::uniform_real_distribution <float> distribution_length(min_length, max_length); // Length
      float L = distribution_length(generator)
      std::uniform_real_distribution <float> distribution_A(min_A, max_A);                // linear coefficient
      float A = distribution_A(generator);
      std::uniform_real_distribution <float> distribution_B(min_B, max_B);                // quadratic coefficient
      float B = distribution_B(generator);
      
      // Take the individual and pass it to the constraint function and update the interesct condition
      intersect = ConstraintARA(R, L, A, B)
    }
  }
  return(antenna)
}
