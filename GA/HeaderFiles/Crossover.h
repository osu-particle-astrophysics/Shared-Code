#pragma once

void crossover(vector<vector<vector<float> > > & varInput, vector<vector<vector<float> > > & varOutput, vector<float> fitness, vector<int> P_loc, vector<int> & selected, float roul_percentage, float tour_percentage, float rank_percentage, int crossover_no, int pool_size, int reproduction_no, float M_rate, float sigma);
