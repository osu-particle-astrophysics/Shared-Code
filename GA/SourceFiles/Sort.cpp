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
#include "Tournament.h"

void Sort(vector<float> & fitness, vector<vector<vector<float> > > & varInput, vector<int> & P_loc)
{
	int i,j,x,y;
	vector<int> O_loc;
	for(int z = 0; z < fitness.size(); z++)
	{
	O_loc.push_back(z);
	}

	for(i = 0; i < fitness.size(); i++)
	{
		double temp = fitness[i];
		int T = O_loc[i];
		vector<vector<vector<float>>> location (1,vector<vector<float> >(NSECTIONS,vector <float>(NVARS, 0.0f)));
		for(int a = 0; a < NSECTIONS; a++)
		{
			for(int b = 0; b < NVARS; b++)
			{
				location[0][a][b] = varInput[i][a][b];
				
			}
		}
		for(j = i; j > 0 && fitness[j-1] < temp; j--)
		{
			fitness[j] = fitness[j-1];
			P_loc[j] = P_loc[j-1];
			for(x = 0; x < NSECTIONS; x++)
			{
				for(y = 0; y < NVARS; y++)
					{
						varInput[j][x][y] = varInput[j-1][x][y];
					}
			}
		}
		fitness[j]=temp;
		P_loc[j] = T;
		for(int a = 0; a < NSECTIONS; a++)
                {
                        for(int b = 0; b < NVARS; b++)
                        {
                                varInput[j][a][b] = location[0][a][b];
                        }
                }
	}
}

