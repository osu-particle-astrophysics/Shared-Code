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
  vector<vector<<float> > antenna = [][]
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
