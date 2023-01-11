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

void Reproduction(vector<vector<vector<float> > > & varInput, vector<vector<vector<float> > > & varOutput, vector<float> fitness, vector<int> P_loc, vector<int> & selected, float roul_percentage, float tour_percentage, float rank_percentage, int reproduction_no, int pool_size, int elite)
{
  // cout << "reproduction flag" << endl;
  //NEED: Current gen; next generation; roul_perecentage, tour_percentage, reproduction_no, fitness, pool_size

  if(elite == 1)
    {
      reproduction_no = reproduction_no - elite;
      int E_select = Elite(fitness);
      for(int i= 0; i<NSECTIONS; i++)
	{
	  for(int j=0; j<NVARS; j++)
	    {
	      varOutput[0][i][j] = varInput[E_select][i][j];
	    }
	  
	}

      selected.push_back(P_loc[E_select]);
    }

  int roul_no = roul_percentage*reproduction_no;
  int tour_no = tour_percentage*reproduction_no;
  int rank_no = rank_percentage*reproduction_no;

  if(reproduction_no == 1)
    {
      roul_no = 1; // this is because roulette will not be left to purely random chance for small population sizes
    }

  while(roul_no + tour_no + rank_no < reproduction_no)
    {
      tour_no += 1;
    }

  if(roul_no > 0)
    {
      //      cout << "roullete flag"<< endl;
      //int r_select = new_roulette(fitness);
      for(int i=elite; i<roul_no + elite; i++)
	{
	  int r_select = new_roulette(fitness); //new_roulette
	  for(int j=0; j<NSECTIONS; j++)
	    {
	      for(int k=0; k<NVARS; k++)
		{
		  varOutput[i][j][k] = varInput[r_select][j][k];
		}
	    
	    }
	  selected.push_back(P_loc[r_select]);
	}
    }
  if(tour_no > 0)
    {
      // cout << "tournament flag"<< endl;
      // int t_select = new_tournament(fitness, pool_size);
      for(int x=roul_no+elite; x<tour_no+roul_no+elite; x++)
	{
	  int t_select = new_tournament(fitness, pool_size);
	  for(int y=0; y<NSECTIONS; y++)
	    {
	      for(int z=0; z<NVARS; z++)
		{
		  varOutput[x][y][z] = varInput[t_select][y][z];
		}
	    }
	  selected.push_back(P_loc[t_select]);
	}
      // cout << "reproduction finished" << endl;
    }
  if(rank_no > 0)
    {
      // cout << "rank flag" << endl;
       for(int r=tour_no+roul_no+elite; r<reproduction_no+elite; r++)
	 {
	   int k_select = Rank(fitness);
           for(int y=0; y<NSECTIONS; y++)
            {
              for(int z=0; z<NVARS; z++)
                {
                  varOutput[r][y][z] = varInput[k_select][y][z];
                }
            }
	   selected.push_back(P_loc[k_select]);
	 }
    }
  if(elite == 1)
    {
      reproduction_no = reproduction_no+elite; 
    }
  //cout << "Roulette Finished" << endl;
}
