#pragma once
vector<vector<vector<float> > > SolveGains(vector<vector<float> > & antenna)
{
  // Declare variables and value vectors
  long double PI = 3.14159265359;
  int Theta_index = 37;     
  vector<float> Theta = {};
  int Phi_index = 72;       
  vector<float> Phi = {};
  int Frequency_index = 60; 
  vector<float> Frequency = {};
  
  // Declare vectors to store important values
  vector<vector<vector<float>>> Gains (Theta_index,vector<vector<float> >(Phi_index,vector <float>(Frequency_index, 0.0f)));
  
  // populate Theta, Phi, and Frequency vector
  float Theta_start = 0; // replace
  for(int i=0; i<Theta_index; i++)
  {
    Theta.push_back(Theta_start);
    Theta_start = Theta_start + 5.0;
  }
  
  float Phi_start = 0; // replace
  for(int i=0; i<Phi_index; i++)
  {
    Phi.push_back(Phi_start);
    Phi_start = Phi_start + 5.0;
  }
  
  float Frequency_start = pow(83.33*10.0, 6.0); // replace
  for(int i=0; i<Frequency_index; i++)
  {
    Frequency.push_back(Frequency_start);
    Frequency_start = Frequency_start + pow(16.67*10.0, 6.0);
  }
  
  // Loop over Theta, Phi, and Frequency and calculate gain for each point
  // Gain should be symetrical for phi and frequency
  for (int i=0; i<Theta_index; i++)
  {
    double COSANGLE = cos(Theta[i]*PI/180.0f);

    long double theta_gain = (antenna[0][0]*(1/2.0)*(1/sqrt(PI)) 
                              + antenna[0][1]*(1/2.0)*sqrt(3/PI)*COSANGLE 
                              + antenna[0][2]*(1/4.0)*sqrt(5/PI)*(3*pow(COSANGLE, 2)- 1) 
                              + antenna[0][3]*(1/4.0)*sqrt(7/PI)*(5*pow(COSANGLE,3)- 3*COSANGLE) 
                              + antenna[0][4]*(3/16.0)*sqrt(1/PI)*(35*pow(COSANGLE,4) - 30*pow(COSANGLE,2)+3) 
                              + antenna[0][5]*(1/16.0)*sqrt(11/PI)*(15*COSANGLE - 70*pow(COSANGLE,3)+63*pow(COSANGLE,5)) 
                              + antenna[0][6]*(1/32.0)*sqrt(13/PI)*(-5 + 105*pow(COSANGLE,2)-315*pow(COSANGLE,4) + 231*pow(COSANGLE,6)) 
                              + antenna[0][7]*(1/32.0)*sqrt(15/PI)*(-35*COSANGLE+ 315*pow(COSANGLE,3) -693*pow(COSANGLE,5) + 429*pow(COSANGLE,7)) 
                              + antenna[0][8]*(1/256.0)*sqrt(17/PI)*(35 - 1260*pow(COSANGLE,2) + 6930*pow(COSANGLE,4) - 12012*pow(COSANGLE,6) + 6435*pow((COSANGLE),8)) 
                              + antenna[0][9]*(1/256.0)*sqrt(19/PI)*(315*COSANGLE- 4620*pow(COSANGLE,3) + 18018*pow(COSANGLE,5) - 25740*pow(COSANGLE,7) + 12155*pow((COSANGLE),9)) 
                              + antenna[0][10]*(1/512.0)*sqrt(21/PI)*(-63 +3465*pow(COSANGLE,2) - 30030*pow(COSANGLE,4) + 90090*pow(COSANGLE,6) -109395*pow((COSANGLE),8)+46189*pow(COSANGLE,10)) 
                              + antenna[0][11]*(1/512.0)*sqrt(23/PI)*(-693*pow(COSANGLE,1) +15015*pow(COSANGLE,3) - 90090*pow(COSANGLE,5) +218790*pow((COSANGLE),7)-230945*pow(COSANGLE,9)+88179*pow(COSANGLE,11)) 
                              + antenna[0][12]*(1/2048.0)*sqrt(25/PI)*(231 -18018*pow(COSANGLE,2) +225225*pow(COSANGLE,4) - 1021020*pow(COSANGLE,6) +2078505*pow((COSANGLE),8)-1939938*pow(COSANGLE,10)+676039*pow(COSANGLE,12)));
                        /*(1+(genes[13]*(16.67*freq)/83.33))**/
   for (int j=0; j<Phi_index; j++)
   {
    for (int k=0; k<Frequency_index; k++)
    {
      // Calculate the spherical harmonics at this point
      Gains[i][j][k] = theta_gain;
    }
   } 
  }
  
  // Return the Gain vector
  return(Gains);
}
