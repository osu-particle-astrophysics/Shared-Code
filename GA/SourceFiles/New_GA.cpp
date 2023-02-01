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


int main()
{
  cout << "Genetic Algorithm initialized" << endl;
  
  // ARGUMENTS (read in all arguments that determine what functions get run) 
  str design = ARA;  string(argv[1]); // read in ARA or PUEO
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
  vector<vector<vector<float>>> varInput (population,vector<vector<float> >(sections,vector <float>(genes, 0.0f))); // stores all input antennas
  vector<vector<vector<float>>> varOutput (population,vector<vector<float> >(sections,vector <float>(genes, 0.0f))); // stores all output antennas
  vector<float> fitness (population, 0.0f); // stores fitness score
  vector<int> selected = [];
  
  // FUNCTION CALLS
  
  // Generation zero functions
  if (generation == 0)
  {
    // if ARA, create ARA atennas
    if (design == "ARA")
    {
      // determine sections and genes for ara
      sections = 2;
      genes = 4;
      
      // generate each individual
      for(int i=0; i<NPOP; i++)
      {
        varOutput [i] = GenerateARA();
      }
    }
    
    // if PUEO, create PUEO antennas
    elseif (design == "PUEO")
    {
      // determine sections and genes for pueo
      sections = 1;
      genes = 9; // Dylan please replace this
      for(int i=0; i<NPOP; i++)
      {
        varOutput [i] = GeneratePUEO();
      }
    }
    // write information to data files
    DataWrite(varOutput, selected);
  }
  //    Initalize(ARA/PUEO)
  
  //    DataWrite
  // Otherwise:
  //    DataRead
  //    Sort
  //    Reproduction
  //    Crossover
  //    Immigration
  //    DataWrite
  
  return 0;
}
