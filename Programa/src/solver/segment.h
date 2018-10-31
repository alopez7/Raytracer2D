#pragma once

#include "vector.h"
#include <stdbool.h>

/** Struct segment*/
struct segment
{
  Vector position1;
  Vector position2;
};

typedef struct segment Segment;

/* Funciones*/

bool segment_segment_colition(Segment* sa, Segment* sb);

/** Colision entre todos los segmentos y la linea entre dos posiciones dadas*/
bool colition(Segment** segments, int segment_count,
   Vector* position1, Vector* position2);

/** Compara dos segmentos en cierto eje segun el centro de gravedad*/
int segment_centre_compare(Segment* s1, Segment* s2, Axis axis);

/** Compara dos segmentos e cierto eje segun segmento completo*/
int segment_axis_compare(Segment* s1, double value, Axis axis);
