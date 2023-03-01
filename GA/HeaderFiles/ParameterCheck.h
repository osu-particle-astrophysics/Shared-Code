#pragma once

// Global Variables
extern int seed;
extern string design;
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
extern bool termination;
extern string error_code;

void ParameterCheck(int argc)
{
  // Check to see if any arguments are not viable
  // If they arent update the termination clause
  
  if (argc != 11)
  {
    termination = true;
    error_code = "ERROR: Improper amount of arguments";
  }
  
  else if (reproduction_no < 0 || crossover_no < 0 || mutation_rate>100 || mutation_rate<0 || sigma<0 || rank_no <0 || roulette_no < 0 || tournament_no < 0 || crossover_0%2 != 0)
  {
    termination = true;
    error_code = "ERROR: One or more arguments are of an improper value. For example, values may not be less than zero";
  }
  
  else if (design != "PUEO" || design != "ARA")
  {
    termination = true;
    error_code = "ERROR: Unknown design. Known designs are PEUO and ARA";
  }
  
  else if (roulette_no+tournament_no+rank_no > population || reproduction_no + crossover_no > population || roulette_no+tournament_no+rank_no < reproduction_no+crossover_no)
  {
    termination = true;
    error_code = "ERROR: Sum of selection or opperator parameters is improper.";
  }
}
