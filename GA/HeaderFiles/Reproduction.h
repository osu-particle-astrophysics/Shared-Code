#pragma once

#include <vector>

#include "Selection.h"

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

void Reproduction(vector<vector<vector<float> > > & varInput, vector<vector<vector<float> > > & varOutput, vector<float> fitness, vector<int> P_loc, vector<int> & selected)
{
    vector<int> locations;
    Selection(reproduction_no, fitness, locations);
    cout << locations[0] << endl;
    
    for(int i=0; i<reproduction_no; i++)
    {
    	selected.push_back(P_loc[locations[i]]);
	for(int j=0; j<sections; j++)
	{
	    for(int k=0; k<genes; k++)
	    {
	    	varOutput[i][j][k] = varInput[locations[i]][j][k];
	    }
	}
    }
    cout << "Reproduction Finished" << endl;
}
