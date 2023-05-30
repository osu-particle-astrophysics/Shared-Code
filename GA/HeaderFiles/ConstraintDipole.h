#pragma once
bool ConstraintDipole(float R, float L)
{
    // Set variables
    bool intersect = true;
    float max_radius = 1.0;
    float min_radius = 0.0;
    float max_length = 1.0;
    float min_length = 0.0;

    // Check to see if antenna meets requirements
    if (R > max_radius || R < min_radius  || L > max_length || L < min_length)
    {
        intersect = true;
    }
    else
    {
        intersect = false;
    }

    // Return interesect condition
    return intersect;
}