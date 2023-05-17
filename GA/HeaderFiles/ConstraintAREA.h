#pragma once
bool ConstraintAREA(vector<vector<float> > antenna)
{
  bool intersect = true;
  
  // Fetch Gains of this antenna design
  vector<vector<vector<float>>> Gains = SolveGains(antenna);
    
  // Use gains to check energy conservation
  // Check if min gain value is negative, if it is, rescale gain coefficents 
  
  return intersect;
}
