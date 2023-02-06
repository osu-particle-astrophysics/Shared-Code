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
#include "Reproduction.h"
#include "Roulette.h"
#include "Selection.h"
#include "Sort.h"
#include "Tournament.h"

int Rank(vector<float> fitness)
{
  vector<float> probabilities;
  float sum_npop=0;
  for(int i=1; i<=fitness.size(); i++)
    {
      sum_npop = sum_npop + i;
    }
  for(int j=0; j<fitness.size(); j++)
    {
      probabilities.push_back((fitness.size()-j)/(sum_npop));
    }

  uniform_real_distribution<float> choice(0.0, 1.0);
  float select = choice(generator);

  int x=0;
  float probability_sum =0;
  for (int k=0; probability_sum <= select; k++)
    {
      probability_sum = probability_sum + probabilities[k];
      x=k;
    }
  return(x);
}
