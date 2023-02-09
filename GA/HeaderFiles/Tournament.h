#pragma once

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
