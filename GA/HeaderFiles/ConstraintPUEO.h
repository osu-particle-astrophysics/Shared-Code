#pragma once


bool ConstraintPUEO(float s, float h, float x_0,
                    float y_0, float y_f, float z_f, float beta,
                    float l, float H)
{
  // Check to see if PUEO antenna conforms

  // Variables
  float max_s = 50.0;
  float max_h = 175.0;
  float min_h = 75.0;
  bool intersect = true;
  float x_f = s;
  // We need to make sure the trapezoid extensions of the ridges
  // don't intersect. To do this, we solve an system of two 
  // equations, each one representing the line of adjacent edges
  // of the trapezoids. Then we check if that intersection is
  // between x_0 - H and x_0 (the height range of the trapezoid)
  float I = (l * x_0 + h * y_0 - x_0 * y_0)/(h + l - y_0)
  // Run checks
  if (s < 0.0 || s > max_s || h > max_h || h < min_h)
  {
    intersect = true;
  }
  else if (x_0 < 0 || x_0 > x_f) 
  {
    intersect = true;
  }
  else if (y_0 < 0 || y_0 > z_f || y_0 > x_0) 
  {
    intersect = true;
  }
  else if (y_f < 0 || y_f > z_f) 
  {
    intersect = true;
  }
  else if (z_f < 0 || z_f > h) 
  {
    intersect = true;
  }
	// Check if trapezoids touch
  else if( I > (x_0 - H) && I < x_0 )
  {
    intersect = true;
  }
  else if ((4.0 / 30.0) * z_f > (beta * 100) 
           || (7 * z_f) < (beta * 100) || 2 < beta) 
  {
    intersect = true;
  }
  else 
  {
    intersect = false;
  }

  return intersect;
}
