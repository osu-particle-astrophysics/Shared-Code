#pragma once

// Includes
#include "SolveGains.h"
#include "FindMin.h"
#include "ScaleAREA.h"

bool ConstraintAREA(vector<vector<float> > & antenna)
{
  bool intersect = true;
  
  // Fetch Gains of this antenna design
  vector<vector<vector<float>>> Gains = SolveGains(antenna);
    
  // Use gains to check energy conservation
  // Check if min gain value is negative, if it is, rescale gain coefficents 
  float Min = 0.0;
  while (intersect == true)
  {
    // Scale the antenna's coefficients
    antenna = ScaleAREA(antenna, Gains);
    
    // Resolve Gains
    vector<vector<vector<float>>> Gains = SolveGains(antenna);
    
    // Double Check that the Min of Gains is not negative
    Min = FindMin(Gains);
    if (Min >= 0.0)
    {
      intersect = false;
    }
  }
  
  // Return the interesect constraint
  return intersect;
}
