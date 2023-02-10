#pragma once

// Global Variables
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

void Crossover(vector<vector<vector<float> > > & varInput, vector<vector<vector<float> > > & varOutput, vector<float> fitness, vector<int> P_loc, vector<int> & selected, float roul_percentage, float tour_percentage, float rank_percentage, int crossover_no, int pool_size, int reproduction_no, float M_rate, float sigma)
{
  // Start Flag
  cout << "Crossover Started" << endl;
	
  // Define Variables
  vector<int> locations;
  double swap;
  uniform_real_distribution<double> choice(0.0, 1.0);

  // call selection methods
  Selection(crossover_no, fitness, locations)

  if(locations.size() != crossover_no)
   {
     cout << "error: parent vector is not proper length" << endl;
   }

//
   for(int i=0; i<locations.size(); i=i+2)
      {
         for(int j=0; j<sections; j++)
            {
	       bool intersect = true;
	       while (intersect == true)
	       {
	          for(int k=0; k<genes; k++)
	          {
	             swap = choice(generator);

	             if(swap < .5)
	                {
		           varOutput[i+reproduction_no][j][k] = varInput[locations[i]][j][k];
		           varOutput[i+1+reproduction_no][j][k] = varInput[locations[i+1]][j][k];
	                }
	             else
	                {
		           varOutput[i+reproduction_no][j][k] = varInput[locations[i+1]][j][k];
		           varOutput[i+1+reproduction_no][j][k] = varInput[locations[i]][j][k];
	                }
	          }
		  
		  if (design == "ARA")
		  {
	             bool intersect_A = true;
                     float R_1= varOutput[i+reproduction_no][j][0];                                                 
                     float l_1= varOutput[i+reproduction_no][j][1]; 
                     float a_1= varOutput[i+reproduction_no][j][2];  
                     float b_1= varOutput[i+reproduction_no][j][3]; 
	             intersect_A = ConstraintARA(R_1, l_1, a_1, b_1);

	             float R_2= varOutput[i+1+reproduction_no][j][0];
                     float l_2= varOutput[i+1+reproduction_no][j][1];
                     float a_2= varOutput[i+1+reproduction_no][j][2];
                     float b_2= varOutput[i+1+reproduction_no][j][3];
		  }     	  
	       }
            }
         selected.push_back(P_loc[parents_loc[i]]);
         selected.push_back(P_loc[parents_loc[1+i]]);
   }
   mutation(varOutput, M_rate, sigma, reproduction_no, crossover_no);
}
