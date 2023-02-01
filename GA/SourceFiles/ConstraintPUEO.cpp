#include <time.h>
#include <math.h>
#include <random>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>

bool ConstraintPUEO(vector<vector<float> > varInput)
{
  bool intersect = true;
  //float max_S = 50;
  //float max_H = 50;
  // these indicies will change depending on how the individual is formatted.
  float S = varInput[0][0];
  float H = varInput[0][1];
  float x_0 = varInput[0][2];
  float x_f = varInput[0][0]; //x_f = S
  float y_0 = varInput[0][3];
  float y_f = varInput[0][4];
  float z_f = varInput[0][5];
  float beta = varInput[0][6];
  
  if(S > max_S || H > max_H){
    intersect = true;
  }else if(x_0 < 0 || x_0 > x_f){
    intersect = true;
  }else if(y_0 < 0 || y_0 > z_f){
    intersect = true;
  }else if(y_f < 0 || y_f > z_f){
    intersect = true;
  }else if(z_f < 0 || z_f > H){
    intersect = true;
  }else if((4/30)*z_f > beta || (7*z_f) < beta){
    intersect = true;
  }else{
    intersect = false;
  }
  return intersect;
}
