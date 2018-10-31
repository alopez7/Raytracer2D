#include "light.h"

double light_intensity(double distance, double intensity)
{
  return pow(M_E,(-(distance*distance)/(2*intensity*intensity)));
}

void light_add_color(Color* base, Light* light, Vector* position)
{
  double distance = vector_distance(position, &light -> position);
  double intensity = light_intensity(distance, light -> intensity);
  base -> R += intensity * light -> color.R;
  base -> G += intensity * light -> color.G;
  base -> B += intensity * light -> color.B;
}
