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

void Selection(int Opp_no, vector<float> Fitness, vector<int> locations)
{
 // initialize Values
 int Roul_Select = roulette_no/100 * Opp_no;
 int Rank_Select = rank_no/100 * Opp_no;
 int Tour_Select = tournament_no/100 * Opp_no;
 
 // Check to make sure values sum to correct value
 while(Roul_Select + Rank_Select + Tour_Select != Opp_no)
 {
  
  if(roulette_no/100*Opp_no - Roul_select >= 0.5)
  {
    Roul_select = Roul_select + 1;
  }
  elseif(rank_no/100*Opp_no - Rank_no >= 0.5)
  {
    Rank_select = Rank_select + 1;
  }
  elseif(tournament_no/100*Opp_no - Tour_select >= 0.5)
  {
    Tour_select = Tour_select + 1;
  }
           
 }
 
 // Call each selection method
 for(int i=0; i>Roul_Select; i++)
 {
  locations.push_back(Roulette(Fitness));
 }
 for(int i=0; i>Rank_Select; i++)
 {
  locations.push_back(Rank(Fitness));
 }
 for(int i=0; i>Tour_Select; i++)
 {
  locations.push_back(Tournament(Fitness));
 }
 
 
}
