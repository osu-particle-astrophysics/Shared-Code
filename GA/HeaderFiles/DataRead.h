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


void DataRead(vector<vector<vector<float> > >& dna_input,
              vector<float>& fitness)
{
  // This function reads in data from various files

  // Establish variables
  int dna_garbage_end = 9;                      // number of header lines
  int csv_file_size = population * sections;
  ifstream generationDNA("generationDNA.csv");
  string csv_content[csv_file_size];
  string str_to_dbl;                            // string to double
  string dumpster;
  for (int i=0; i<dna_garbage_end; i++)         // getting rid of headers
  {
    getline(generationDNA, dumpster);           // std::getline()
  }

  for (int i=0; i<csv_file_size; i++)           // start reading
  {
    getline(generationDNA, csv_content[i]);     // std::getline()
    int j = i / sections;                       // j: individual index
    int p = i - sections * j;                   // p: section index
    istringstream stream(csv_content[i]);
    for (int k = 0; k < genes; k++)
    {
      getline(stream, str_to_dbl, ',');
      dna_input[j][p][k] = atof(str_to_dbl.c_str());
    }
  }

  generationDNA.close();

  // Now we need to read fitness scores:

  ifstream fitnessScores;
  fitnessScores.open("fitnessScores.csv");
  string fitness_read[population + 2];

  for (int i = 0; i < (population + 2); i++)
  {
    getline(fitnessScores, fitness_read[i]);
    if (i >= 2)
    {
      fitness[i - 2] = atof(fitness_read[i].c_str());
      if (fitness[i - 2] < 0)
      {
        fitness[i - 2] = 0;
      }
    }
  }

  fitnessScores.close();

}
