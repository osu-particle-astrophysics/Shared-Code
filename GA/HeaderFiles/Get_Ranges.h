#pragma once

#include <vector>
extern string design;
extern int genes;


void Get_Ranges(float &variable_max, float &variable_min, int gene)
{
  // Establish max and min range vectors for each design

  if (design == "ARA")
  {
    // ARA ranges
    vector<float> max{7.5, 140.0, 1.0, 1.0};
    vector<float> min{0, 10.0, -1.0, -1.0};
  }
  else if (design == "PUEO")
  {
    // PUEO ranges
    vector<float> max{50.0, 175, 50.0, 50.0, 175.0, 175.0, 12.25};
    vector<float> min{0.0, 75.0, 0.0, 0.0, 0.0, 0.0, 0.0}
  }
  else if (design == "AREA")
  {
    // AREA ranges
    vector<float> max{5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0 };
    vector<float> min{-5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0};
  }
  else if (design == "Symmetric Dipole" || design == "Asymmetric Dipole")
  {
    // Dipole ranges
    float max{ 10.0, 10000.0 };
    float min{ 0.25, 200.0 };
  }

  // Find value for the gene that is being mutated. 
  for (int i = 0; i < genes; i++)
  {
    if (i == gene)
    {
      variable_max = max[i];
      variable_min = min[i];
    }
  }