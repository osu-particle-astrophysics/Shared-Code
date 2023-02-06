
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

void DataRead(vector<vector<vector<float> > >& varInput, vector<float>& fitness)
{
  ifsteam generationDNA;
  generationDNA.open("generationDNA.csv");
  int csv_file_size = DNA_GARBAGE_END + (NPOP * NSECTIONS);
  string csvContent[csv_file_size];                              // Contain each line of the csv file
  string strToDbl;                                               // Data change from string to float, then written into verInput or fitness

  // This loop reads through the .csv file line by line
  // If we're in data (past line 9), it reads in the line

  for(int i=0; i<csv_file_size; i++)
    {
      getline(generationDNA, csvContent[i]);
      if (i>=DNA_GARBAGE_END)
	{
	  double j=floor((i-DNA_GARBAGE_END)/NSECTIONS);         // Figure out which individual we're looking at
	  int p=i-DNA_GARBAGE_END - NSECTIONS * j;               // pulls out which row of their matrix we're looking at
	  istringstream stream(csvContent[i]);
	  for (int k=0; k<NVARS; k++)
	    {
	      getline(stream, strToDbl, ',');
	      varInput[j][p][k] = atof(strToDbl.c_str());
	    }
	}
    }

  generationDNA.close();

  // Now we need to read fitness scores:

  ifstream fitnessScores;
  fitnessScores.open("fitnessScores.csv");
  string fitnessRead[NPOP+2];

  ifstream fitnessScores;
  fitnessScores.open("fitnessScores.csv");
  string fitnessRead[NPOP+2];

  for (int i=0; i<(NPOP+2); i++)
    {
      getline(fitnessScores, fitnessRead[i]);
      if (i>=2)
	{
	  fitness[i-2] = atof(fitnessRead[i].c_str());
	  if (fitness[i-2]<0)
	    {
	      fitness[i-2] = 0;                                 // If the fitness Score is less than 0, we set it to 0 to not throw things off
 	    }
	}
    }
  
  fitnessScores.close();

}
