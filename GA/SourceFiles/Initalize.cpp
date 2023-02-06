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

// User functions
#include "ConstraintARA.h"
#include "ContraintPUEO.h"
#include "Crossover.h"
#include "DataRead.h"
#include "DataWrite.h"
#include "GenerateARA.h"
#include "GeneratePUEO.h"
#include "Immigration.h"
#include "Initialize.h"
#include "Mutation.h"
#include "Rank.h"
#include "Reproduction.h"
#include "Roulette.h"
#include "Selection.h"
#include "Sort.h"
#include "Tournament.h"

void Initialize(vector<vector<vector<float> > > & varOutput, str design)
{
// if the experiment is ARA, then call GenerateARA 
  if(design == "ARA")
  {
    for(int i=0; i<population; i++)
    {
      varOutput[i] = GenerateARA(); 
    }
  }
  
// if the experiment is PUEO, then call GeneratePUEO 
   if(design == "PUEO")
  {
    for(int i=0; i<population; i++)
    {
      varOutput[i] = GeneratePUEO();
    }
  }
}

