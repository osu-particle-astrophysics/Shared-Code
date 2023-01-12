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

int Roulette(vector<float> fitness)
{
  vector<float> probabilities;
  float total_fitness = 0;

  for(int i=0; i< fitness.size();i++)
    {
      total_fitness = total_fitness + fitness[i];
    }
  for(int j =0; j< fitness.size();j++)
    {
      probabilities.push_back(fitness[j]/total_fitness);
    }

  uniform_real_distribution<float> choice(0.0, 1.0);
  float select = choice(generator);

  int x=0;
  float probability_sum = 0;
  for(int i=0; probability_sum <= select; i++)
    {
      probability_sum = probability_sum + probabilities[i];
      x=i;
    }
  return(x);
}
