#pragma once

#include <vector>
#include <random>
extern int genes;
extern int sections;
extern int seed;
extern std::default_random_engine generator;

std::vector<std::vector<float> > GenerateDipole()
{
    // initialize an interesect condidtion
    bool intersect = true;
    std::vector<std::vector<float> > antenna(sections, std::vector <float>(genes, 0.0f));

    // variables
    float max_radius = 1.0;
    float min_radius = 0.0;
    float max_length = 1.0;
    float min_length = 0.0;  
    float R, L;
    for (int i = 0; i < sections; i++)
    {
        // while the intersect condition is true, generate the side of an individual
        intersect = true;
        while (intersect == true)
        {
            // Generate gene for the radius
            std::uniform_real_distribution <float> distribution_radius(min_radius, max_radius); 
            R = distribution_radius(generator);

            // Generate gene for the length
            std::uniform_real_distribution <float> distribution_length(min_length, max_length); 
            L = distribution_length(generator);

            // Take the individual and pass it to the constraint function and update the interesct condition
            intersect = ConstraintDipole(R, L);
        }
        // store the variables into the antenna std::vector
        antenna[i][0] = R;
        antenna[i][1] = L;
    }
    return(antenna);
}
