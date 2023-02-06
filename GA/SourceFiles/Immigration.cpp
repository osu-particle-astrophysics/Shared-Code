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
#include "Initialize.h"
#include "Mutation.h"
#include "Rank.h"
#include "Reproduction.h"
#include "Roulette.h"
#include "Selection.h"
#include "Sort.h"
#include "Tournament.h"

void Immigration(vector<vector<vector<float> > > & varOutput, int reproduction_no, int crossover_no, float max_length, float max_radius, float max_seperation, float max_outer_radius, float max_A, float max_B)
{
  uniform_real_distribution<float> l_mut(min_length, max_length);
  uniform_real_distribution<float> r_mut(0, max_radius);
  uniform_real_distribution<float> a_mut(min_A, max_A);
  uniform_real_distribution<float> b_mut(min_B, max_B);
  uniform_real_distribution<float> s_mut(min_seperation, max_seperation);

  for(int i=reproduction_no+crossover_no; i< varOutput.size(); i++)
    {
      for(int j=0; j<NSECTIONS; j++)
	{
	  varOutput[i][j][0] = r_mut(generator);
	  varOutput[i][j][1] = l_mut(generator);
	  varOutput[i][j][2] = a_mut(generator);
	  varOutput[i][j][3] = b_mut(generator);
	  varOutput[i][j][4] = s_mut(generator);

          float R= varOutput[i][j][0]; 
          float l= varOutput[i][j][1]; 
          float a= varOutput[i][j][2]; 
          float b= varOutput[i][j][3]; 
          float end_point = (a*l*l + b*l + R); 
          float vertex = (R - (b*b)/(4*a)); 

	  if(a == 0.0 && max_outer_radius > end_point && end_point >= 0.0)
	    {
	      j=j;
	    }
          else if(a != 0.0 && max_outer_radius > end_point && end_point >= 0.0 && max_outer_radius > vertex && vertex >= 0.0)
	  {
            j= j;
          }
          else{
            j= j-1;
          }
	  
	}
    }
}
