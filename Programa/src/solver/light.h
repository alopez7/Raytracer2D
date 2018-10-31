#pragma once

#include "color.h"
#include "vector.h"

/** Struct con las luces */
struct light
{
  /** Posicion dada por un vector*/
  Vector position;
  Color color;
  double intensity;
};

typedef struct light Light;

/** Funciones */

/** Retorna lel color de la luz dada la posicion*/
void light_add_color(Color* base, Light* light, Vector* position);
