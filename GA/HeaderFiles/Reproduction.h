#pragma once

extern int seed = time(NULL);
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

void reproduction(vector<vector<vector<float> > > & varInput, vector<vector<vector<float> > > & varOutput, vector<float> fitness, vector<int> P_loc, vector<int> & selected, float roul_percentage, float tour_percentage, float rank_percentage, int reproduction_no, int pool_size, int elite);
