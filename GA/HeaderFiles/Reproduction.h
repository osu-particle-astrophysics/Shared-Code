#pragma once

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
    
    for(int i=0; i<reproduction_no; i++)
    {
    	selected.push_back(varInput[locations[i]);
	for(int j=0; j<Sections; j++)
	{
	    for(int k=0; k<Parameters; k++)
	    {
	    	varOutput[i][j][k] = varInput[locations[i]][j][k];
	    }
	}
    }
}
