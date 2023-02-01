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

vector<vector<float>> Generate(int sections, int genes)
{
  //initialize variables
  //int max_S = 50; //might not need the max variables in this file
  //int max_H = 50;
  vector<vector<float> > outputVector (sections, vector<float>(genes, 0.0f));
  bool intersect = true;
  for(int i=0; i < sections; i++){
    while(intersect==true){ //while the antenna intersects, generate new values for antena (S, m, H, x_0, y_0, z_0, x_f, y_f, z_f, tau, beta)
      
      std::uniform_real_distribution <float> distribution_S(0, max_S);  //Side length (= x_f)
      float S = distribution_S(generator);
      std::uniform_real_distribution <float> distribution_H(0, max_H);  //Height 
      float H = distribution_H(generator);
      std::uniform_real_distribution <float> distribution_X0(0, S);  //x_0
      float X0 = distribution_X0(generator);
      std::uniform_real_distribution <float> distribution_Y0(0, X0); //y_0
      float Y0 = distribution_H(generator);
      std::uniform_real_distribution <float> distribution_ZF(0, H);  //z_f
      float ZF = distribution_ZF(generator);
      std::uniform_real_distribution <float> distribution_YF(0, ZF);  //y_f
      float YF = distribution_YF(generator);
      std::uniform_real_distribution <float> distribution_beta((4/30)*ZF, 7*ZF);  //beta, upper bound is arbitrary, can adjust if needed
      float beta = distribution_beta(generator)/100;
      float tau = 0.26;  //tau must be 0.26
      float m = 1;  //we are only evolving m = 1 for now.
      outputVector[i][0] = S;
      outputVector[i][1] = H;
      outputVector[i][2] = X0;
      outputVector[i][3] = Y0;
      outputVector[i][4] = YF;
      outputVector[i][5] = ZF;
      outputVector[i][6] = beta;
      outputVector[i][7] = m;
      outputVector[i][8] = tau;
      intersect = ConstraintPUEO(outputVector);
    }
  }
  return outputVector;

}
