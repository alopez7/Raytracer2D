#include "color.h"


Color* color_init(double r, double g, double b)
{
  Color* color = malloc(sizeof(Color));
  color -> R = r;
  color -> G = g;
  color -> B = b;
  return color;
}
