#pragma once

extern int seed;
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
