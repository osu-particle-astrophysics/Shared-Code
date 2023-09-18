#pragma once

#include <algorithm>
#include <random>

// User Functions
#include "ConstraintARA.h"
#include "ConstraintPUEO.h"
#include "ConstraintAREA.h"
#include "Selection.h"
#include "Mutation.h"
#include "Failure.h"

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


void Crossover(vector<vector<vector<float> > >& dna_input, 
               vector<vector<vector<float> > >& dna_output, 
               vector<float> fitness, vector<int> p_loc, 
               vector<int>& selected)
{
  // Generate a pair of children from a pair of selected parents

  // Start Flag
  cout << "Crossover Started" << endl;

  // Define Variables
  vector<int> locations;
  vector<int> spare_locations;
  double exchange;
  uniform_int_distribution<int> choice(0, 1);

  // call selection methods to populate locations
  Selection(crossover_no, fitness, locations);

  // call selection to populate spare locations
  Selection(10*crossover_no, fitness, spare_locations);

  uniform_int_distribution<int> grab(0, spare_locations.size()-1);

  // shuffle vector
  auto rng = default_random_engine{};
  shuffle(begin(locations), end(locations), rng);
  shuffle(begin(spare_locations), end(spare_locations), rng);


  // Check the size of location vector
  if (locations.size() != crossover_no)
  {
    cout << "error: parent vector is not proper length" << endl;
  }

  // Crossover two antennas to make 2 children
  for (int i = 0; i < crossover_no; i = i + 2)
  {
    // Force parents to be different
    int trials = 0;
    int max_trials = population*population; // may need adjusting
    //cout << "Choosing parents" << endl;
    while (dna_input[locations[i]] == dna_input[locations[i + 1]])
    {
      trials = trials + 1;
      //cout << "Identical parents detected, choosing new parents" << endl;
      int new_parent = grab(generator);
      int new_parent2 = grab(generator);
      swap(locations[i], spare_locations[new_parent]);
      swap(locations[i + 1], spare_locations[new_parent2]);

      // failsafe exit
      if (dna_input[locations[i]] == dna_input[locations[i + 1]] && trials > max_trials)
      {
        // If the trials is above threshold, exit code
        cout << "Crossover Failed" << endl;
        string cause = "To many identical parents.";
        Failure(cause);
        exit(0);
      }
    }

    // If the children are identical to their parent,
    // Or if an intersect is present on either side.
    // Find a new parent set
    trials = 0;
    bool identical = true;
    bool intersect = true;
    while (identical == true || intersect == true)
    {
      trials = trials + 1;
      //cout << "Attempting crossover, trial: " << trials << endl;
      for (int j = 0; j < sections; j++)
      {
        for (int k = 0; k < genes; k++)
        {
          // Swap genes between parents to create the children
          exchange = choice(generator);
          if (exchange == 1)
          {
            dna_output[i + reproduction_no][j][k]
              = dna_input[locations[i]][j][k];

            dna_output[i + 1 + reproduction_no][j][k]
              = dna_input[locations[i + 1]][j][k];
          }
          else if (exchange == 0)
          {
            dna_output[i + reproduction_no][j][k]
              = dna_input[locations[i + 1]][j][k];

            dna_output[i + 1 + reproduction_no][j][k]
              = dna_input[locations[i]][j][k];
          }
        }
      }

      // Call constraint functions to check for intersects
      if (design == "ARA")
      {
        //cout << "Checking Constraints." << endl;
        vector<vector<bool> > section_intersect(2, vector<bool>(sections, true));

        // Define output vectors and check intersects
        for (int a = 0; a < 2; a++)
        {
          for (int j = 0; j < sections; j++)
          {
            vector<float> output = dna_output[i + a + reproduction_no][j];
            section_intersect[a][j] = ConstraintARA(output[0], output[1],
                                                    output[2], output[3]);
            cout << section_intersect[a][j] << endl;
            output.clear();
          }
        }

        // Count how many intersections there were
        int intersections = 0;
        for (int a = 0; a < 2; a++)
        {
          intersections = intersections + count(section_intersect[a].begin(),
                                                section_intersect[a].end(),
                                                true);
        }
        cout << intersections << endl;
        if (intersections == 0)
        {
          intersect = false;
        }
      }

      else if (design == "PUEO")
      {
        // Call constraint PUEO for variables
        //cout << "Checking Constraints." << endl;
        vector<vector<bool> > section_intersect(2, vector<bool>(sections, true));

        // Define output vectors and check intersects
        for (int a = 0; a < 2; a++)
        {
          for (int j = 0; j < sections; j++)
          {
            vector<float> output = dna_output[i + a + reproduction_no][j];
            section_intersect[a][j] = ConstraintPUEO(output[0], output[1], output[2],
                                                     output[3], output[4], output[5],
                                                     output[6]);
          }
        }

        // Count how many intersections there were
        int intersections = 0;
        for (int a = 0; a < 2; a++)
        {
          intersections = intersections + count(section_intersect[a].begin(),
            section_intersect[a].end(),
            true);
        }
        if (intersections == 0)
        {
          intersect = false;
        }
      }

      else if (design == "AREA")
      {
        // Call constraint AREA for variables

        //cout << "Checking Constraints." << endl;
        vector<bool> section_intersect(2, true);

        // Define output vectors and check intersects
        for (int a = 0; a < 2; a++)
        {
          section_intersect[a] = ConstraintAREA(dna_output[i + a + reproduction_no]);
        }

        // Count how many intersections there were
        int intersections = 0;
        for (int a = 0; a < 2; a++)
        {
          intersections = intersections + count(section_intersect.begin(),
                                                section_intersect.end(),
                                                true);
        }
        if (intersections == 0)
        {
          intersect = false;
        }
      }

      else if (design == "Symmetric Dipole" || design == "Asymmetric Dipole")
      {
        // Call constraint Dipole for variables
        //cout << "Checking Constraints." << endl;
        vector<vector<bool> > section_intersect(2, vector<bool>(sections, true));

        // Define output vectors and check intersects
        for (int a = 0; a < 2; a++)
        {
          for (int j = 0; j < sections; j++)
          {
            vector<float> output = dna_output[i + a + reproduction_no][j];
            section_intersect[a][j] = ConstraintDipole(output[0], output[1]);
          }
        }

        // Count how many intersections there were
        int intersections = 0;
        for (int a = 0; a < 2; a++)
        {
          intersections = intersections + count(section_intersect[a].begin(),
                                                section_intersect[a].end(),
                                                true);
        }
        if (intersections == 0)
        {
          intersect = false;
        }
      }

      // Check to see if children are identical to parents
      if ((dna_output[i + reproduction_no] == dna_input[locations[i]])
        || (dna_output[i + 1 + reproduction_no] == dna_input[locations[i + 1]])
        || (dna_output[i + reproduction_no] == dna_input[locations[i + 1]])
        || (dna_output[i + 1 + reproduction_no] == dna_input[locations[i]]))
      {
        identical = true;
      }
      else
      {
        identical = false;
      }

      // If either the intersect or identical condition are true,
      // Do one of two things
      if ((identical == true || intersect == true) && trials <= max_trials)
      {
        // Try new Parents
        //cout << "Try new parents" << endl;
        int new_parent = grab(generator);
        int new_parent2 = grab(generator);
        swap(locations[i], spare_locations[new_parent]);
        swap(locations[i + 1], spare_locations[new_parent2]);
      }
      else if ((identical == true || intersect == true) && trials > max_trials)
      {
        // Declare failure
        cout << "Crossover Failed" << endl;
        string cause = "No viable children.";
        Failure(cause);
        exit(0);
      }
      
    }
    // Save location of the parent antennas
    selected.push_back(p_loc[locations[i]]);
    selected.push_back(p_loc[locations[1 + i]]);
  }

  // End Flag
  cout << "Crossover Complete" << endl;
}
