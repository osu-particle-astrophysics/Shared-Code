#pragma once
extern int seed;
extern default_random_engine generator(seed);
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
  int pool_size = 0.07*population;
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
