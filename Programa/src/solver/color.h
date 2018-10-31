#pragma once
#include <stdlib.h>

/** Struct con que representa un color RGB */
struct color
{
  /** valor 0-1 de rojo*/
  double R;
  /** valor 0-1 de verde*/
  double G;
  /** valor 0-1 de azul*/
  double B;
};

typedef struct color Color;

/* Funciones */

Color* color_init(double r, double g, double b);
