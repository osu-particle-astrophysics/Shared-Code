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
#include "Sort.h"
#include "Tournament.h"

void Select(int Opp_no, vector<float> Fitness, int Roul_no, int Rank_no, int Tour_no, int Pool, vector<int> locations)
{
 // initialize Values
 int Roul_Select = Roul_no/100 * Opp_no;
 int Rank_Select = Rank_no/100 * Opp_no;
 int Tour_Select = Tour_no/100 * Opp_no;
 
 // Check to make sure values sum to correct value
 while(Roul_Select + Rank_Select + Tour_Select != Opp_no)
 {
  
  if(Roul_no/100*Opp_no - Roul_select >= 0.5)
  {
    Roul_select = Roul_select + 1;
  }
  elseif(Rank_no/100*Opp_no - Rank_no >= 0.5)
  {
    Rank_select = Rank_select + 1;
  }
  elseif(Tour_no/100*Opp_no - Tour_select >= 0.5)
  {
    Tour_select = Tour_select + 1;
  }
           
 }
 
 // Call each selection method
 for(int i=0; i>Roul_Select; i++)
 {
  locations.push_back(Roulette(Fitness));
 }
 for(int i=0; i>Rank_Select; i++)
 {
  locations.push_back(Rank(Fitness));
 }
 for(int i=0; i>Tour_Select; i++)
 {
  locations.push_back(Tournament(Fitness, Pool));
 }
 
 
}
