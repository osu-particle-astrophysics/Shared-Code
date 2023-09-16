#pragma once

#include <algorithm>
#include <random>

// User Functions
#include "ConstraintARA.h"
#include "ConstraintPUEO.h"
#include "ConstraintAREA.h"
#include "Selection.h"
#include "Mutation.h"

// Global Variables
extern int seed;
extern string design;
extern int generation;
extern int population;
extern int sections;
extern int genes;
extern int reproduction_no;
extern int crossover_no;
extern int mutation_no;
extern int sigma;
extern int rank_no;
extern int roulette_no;
extern int tournament_no;

void Failure(string cause)
{
  ofstream failure;
  failure.open("failure.txt");
  failure << "Evolution Failed: " << cause ;
  failure.close();
}