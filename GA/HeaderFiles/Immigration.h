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

void immigration(vector<vector<vector<float> > > & varOutput, int reproduction_no, int crossover_no, float max_length, float max_radius, float max_sepration, float max_outer_radius, float max_A, float max_B);
