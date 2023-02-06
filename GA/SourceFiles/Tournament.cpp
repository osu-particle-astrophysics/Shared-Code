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
#include "Rank.h"
#include "Reproduction.h"
#include "Roulette.h"
#include "Selection.h"
#include "Sort.h"
#include "Tournament.h"

int Tournament(vector<float> fitness, int pool_size)
{
 
  vector<int> contenders; 
  uniform_real_distribution<float> choice(0, fitness.size());

  for( int i =0; i<pool_size; i++)
    {
      random_num = rand() % fitness.size();
      contenders.push_back(random_num);
    }

  int max = 0; 
  for(int j=0; j<pool_size; j++) 
    {
      if(fitness[contenders[j]] > fitness[contenders[max]]) 
	{
	  max = j;
	}
    }

  return(contenders[max]);
  
}
