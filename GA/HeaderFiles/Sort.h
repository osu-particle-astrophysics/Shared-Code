#pragma once

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


void Sort(vector<float>& fitness, vector<vector<vector<float> > >& dna_input,
                                  vector<int>& parent_location)
{
  // Sort individuals by fitness score

  // Establish variables
  int i, j, x, y;
  int size = int(fitness.size()); // size=population=fitness.size()

  for (i=0; i<size; i++)
  {
    // temporary variables: temp, t, location; these are used to store the
    //                      current values in the for loop.
    double temp = fitness[i];     // for sorting fitness (high to low)
    vector<vector<vector<float>>> location(1, vector<vector<float> >
                                          (sections, vector <float>
                                          (genes, 0.0f)));
    location[0] = dna_input[i];   // for sorting dna_input based on fitness

    
    for (j = i; j > 0 && fitness[j - 1] < temp; j--)
    {
      fitness[j] = fitness[j - 1]; // sorting fitness in order (high to low)
      parent_location[j] = parent_location[j - 1];
      dna_input[j]=dna_input[j-1]; // sorting dna_input based on fitness
    }

    // Fill in last individual
    fitness[j] = temp;
    parent_location[j] = i;
    dna_input[j] = location[0];
  }
}
