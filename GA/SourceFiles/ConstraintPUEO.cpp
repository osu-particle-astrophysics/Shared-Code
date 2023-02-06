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

// User functions
#include "ConstraintARA.h"
#include "Crossover.h"
#include "DataRead.h"
#include "DataWrite.h"
#include "GenerateARA.h"
#include "GeneratePUEO.h"
#include "Immigration.h"
#include "Initialize.h"
#include "Mutation.h"
#include "Rank.h"
#include "Reproduction.h"
#include "Roulette.h"
#include "Selection.h"
#include "Sort.h"
#include "Tournament.h"

bool ConstraintPUEO(float S, float H, float x_0, float y_0, float y_f, float z_f, float beta)
{
  bool intersect = true;
  float x_f = S;
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
