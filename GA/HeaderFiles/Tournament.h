#pragma once

// Libraries
#include <random>
#include <algorithm>

// Global Variables
extern int seed;
extern std::default_random_engine generator;
extern int generation;
extern int population;
extern int sections;
extern int genes;
extern int reproduction_no;
extern int crossover_no;
extern int mutation_rate;
extern int sigma;
extern int rank_no;
extern int roulette_no;
extern int tournament_no;


int Tournament(vector<float> fitness)
{
  // Define starting parameters
  int pool_size = 2; //0.07 * population;
  if (pool_size < 2)
  {
    pool_size = 2;
  }
  vector<int> contenders;
  int random_num = 0;
  uniform_real_distribution<float> choice(0, fitness.size());

  // Select contenders for the tournament 
  // Don't allow for duplicates
  int i = 0;
  while (i < pool_size)
  {
    // Choose random indvidual
    random_num = choice(generator);

    // If the list is empy add the individual
    if (!contenders.empty())
    {
      contenders.push_back(random_num);
      i = i + 1;
    }
    // If the list contains the individual, do not itterate
    else if (find(contenders.begin(), contenders.end(), random_num) != contenders.end())
    {
      i = i;
    }
    // Otherwise add the individual to the list
    else
    {
      contenders.push_back(random_num);
      i = i + 1;
    }
  }

  // Find the best individual from the contenders
  int max = 0;
  for (int j = 0; j < pool_size; j++)
  {
    if (fitness[contenders[j]] > fitness[contenders[max]])
    {
      max = j;
    }
  }

  // Return the best individual
  return(contenders[max]);

}
