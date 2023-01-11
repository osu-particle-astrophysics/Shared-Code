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

int Tournament(vector<float> fitness, int pool_size)
{
  //needs: fitness, previous gen, random generator;
 
  vector<int> contenders; // tounament pool individuals
  int random_num; // random number from 0-length of the fitness vector
  uniform_real_distribution<float> choice(0, fitness.size());

  for( int i =0; i<pool_size; i++)
    {
      // generate random integer
      random_num = rand() % fitness.size();
      // cout << random_num << endl;
      // place integer number in contenders vector
      contenders.push_back(random_num);
    }

  int max = 0; 
  for(int j=0; j<pool_size; j++) 
    {
     // compare fitness scores coresponding to the integers in contenders
      if(fitness[contenders[j]] > fitness[contenders[max]]) // changed for ryan's test make sure this is a greater than sign for main loop Always check to make sure this is a greater than sign
	{
	  max = j;
	}
    }
  // return the integer that corresponds to the highest fitness score

  return(contenders[max]);
  
}
