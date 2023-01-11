// This function given the number of antannas, a vector to store the antennas and the experiment, will generate
// the zeroth generation of antennas.

// Includes
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

void Initialize(vector<vector<vector<float> > > & varOutput, str experiment)
{
// Code
// if the experiment is ARA, then call GenerateARA for NPop individuals
  if(experiment == "ARA")
  {
    for(int i=0; i<NPop; i++)
    {
      varOutput[i] = GenerateARA() 
    }
  }
  
// if the experiment is PUEO, teh call GeneratePUEO for NPop individuals
   if(experiment == "PUEO")
  {
    for(int i=0; i<NPop; i++)
    {
      varOutput[i] = GeneratePUEO()
    }
  }
}

