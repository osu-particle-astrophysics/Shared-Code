// New_GA.cpp
// Author: Ryan Debolt, Dylan Wells
// Organization: GENETIS
// Date: 12/5/2022
// Info:
// This New version of the GA is designed to house the functions as standalone functions that can be transplanted
// to any GA  with the plan to make the GA as simple and flexible as possible

// Libraries
#include <time.h>
#include <math.h>
#include <random>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;

// User functions
#include "../HeaderFiles/ConstraintARA.h"
#include "../HeaderFiles/ConstraintPUEO.h"
#include "../HeaderFiles/Crossover.h"
#include "../HeaderFiles/DataRead.h"
#include "../HeaderFiles/DataWrite.h"
#include "../HeaderFiles/GenerateARA.h"
#include "../HeaderFiles/GeneratePUEO.h"
#include "../HeaderFiles/Immigration.h"
#include "../HeaderFiles/Initialize.h"
#include "../HeaderFiles/Mutation.h"
#include "../HeaderFiles/Rank.h"
#include "../HeaderFiles/Reproduction.h"
#include "../HeaderFiles/Roulette.h"
#include "../HeaderFiles/Selection.h"
#include "../HeaderFiles/Sort.h"
#include "../HeaderFiles/Tournament.h"


// GLOBAL CONSTANTS

int seed = time(NULL);
default_random_engine generator(seed);
int generation;
int population;
int sections;
int genes;
int reproduction_no;
int crossover_no;
int mutation_rate;
int sigma; 


int main(int argc, char const *argv[])
{
  cout << "Genetic Algorithm initialized" << endl;
  
  // ARGUMENTS (read in all arguments that determine what functions get run) 
  string design = string(argv[1]); // read in ARA or PUEO
  generation = atoi(argv[2]);
  population = atoi(argv[3]); // read in : atoi(argv[x])
  rank_no = atoi(argv[4]);
  roulette_no = atoi(argv[5]);
  tournament_no = atoi(argv[6]);
  reproduction_no = atoi(argv[7]);
  crossover_no = atoi(argv[8]);
  mutation_rate = atoi(argv[9]);
  sigma = atoi(argv[10]);
  
  
  // VECTORS
  vector<int> P_loc (population); // Parent locations vector
  vector<float> fitness (population, 0.0f); // stores fitness score
  vector<int> selected = [];
  
  // Check the design and prepare input/output vectors
  if (design == "ARA")
    {
      // determine sections and genes for ara
      sections = 2;
      genes = 4;
      
      // create vectors based on parameters
      vector<vector<vector<float>>> varInput (population,vector<vector<float> >(sections,vector <float>(genes, 0.0f))); // stores all input antennas
      vector<vector<vector<float>>> varOutput (population,vector<vector<float> >(sections,vector <float>(genes, 0.0f))); // stores all output antennas
    }
    
    // if PUEO, create PUEO antennas
  else if (design == "PUEO")
    {
      // determine sections and genes for PUEO
      sections = 1;
      genes = 7; 
      
      // create vectors based on parameters
      vector<vector<vector<float>>> varInput (population,vector<vector<float> >(sections,vector <float>(genes, 0.0f))); // stores all input antennas
      vector<vector<vector<float>>> varOutput (population,vector<vector<float> >(sections,vector <float>(genes, 0.0f))); // stores all output antennas
    }
  
  // FUNCTION CALLS
  
  // Generation zero functions
  if (generation == 0)
  {
    // run initialization
    Initialize(varOutput, design);
    
    // write information to data files
    DataWrite(varOutput, selected);
  }
  
  // Generation 1+ functions
  //    DataRead
  //    Sort
  //    Reproduction
  //    Crossover
  //    Immigration
  //    DataWrite
  
  return 0;
}
