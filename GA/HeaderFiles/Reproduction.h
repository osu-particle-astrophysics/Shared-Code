#pragma once


void Reproduction(vector<vector<vector<float> > > & varInput, vector<vector<vector<float> > > & varOutput, vector<float> fitness, vector<int> P_loc, vector<int> & selected, float roul_percentage, float tour_percentage, float rank_percentage, int reproduction_no, int pool_size, int elite)
{
    vector<int> locations = [];
    Selection(Reproduction_no, fitness, Roul_no, Rank_no, Tour_no, Pool);
    
    for(int i=0; i<Reproduction_no; i++)
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
