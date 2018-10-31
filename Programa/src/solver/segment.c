#include "segment.h"
#include <stdio.h>

/** Colision entre dos segmentos*/
bool segment_segment_colition(Segment* sa, Segment* sb)
{
  double x1 = sa -> position1.X;
  double x2 = sa -> position2.X;
  double y1 = sa -> position1.Y;
  double y2 = sa -> position2.Y;
  double x3 = sb -> position1.X;
  double x4 = sb -> position2.X;
  double y3 = sb -> position1.Y;
  double y4 = sb -> position2.Y;
  double det = (x1-x2)*(y4-y3)-(y1-y2)*(x4-x3);
  if (det == 0) return false;
  double c1 = x1-x2;
  double c2 = x4-x3;
  double c3 = y1-y2;
  double c4 = y4-y3;
  double c5 = x4-x2;
  double c6 = y4-y2;
  double alpha = (c4*c5-c2*c6)/det;
  double beta = (c1*c6-c3*c5)/det;
  if (alpha < 0 || alpha > 1 || beta < 0 || beta > 1) return false;
  return true;
}

/** Colision entre todos los segmentos y la linea entre dos posiciones dadas*/
bool colition(Segment** segments, int segment_count,
  Vector* position1, Vector* position2)
{
  for (int i = 0; i < segment_count; i++)
  {
    Segment line;
    line.position1 = *position1;
    line.position2 = *position2;
    if (segment_segment_colition(segments[i], &line))
    {
      return true;
    }
  }
  return false;
}

/** Compara dos segmentos en cierto eje segun el centro de gravedad*/
int segment_centre_compare(Segment* s1, Segment* s2, Axis axis)
{
  double centre1, centre2;
  if (axis == X)
  {
    centre1 = s1 -> position1.X + s1 -> position2.X;
    centre2 = s2 -> position1.X + s2 -> position2.X;
  }
  else
  {
    centre1 = s1 -> position1.Y + s1 -> position2.Y;
    centre2 = s2 -> position1.Y + s2 -> position2.Y;
  }
  if (centre1 < centre2)
  {
    return -1;
  }
  else if (centre1 == centre2)
  {
    return 0;
  }
  return 1;
}

/** Compara dos segmentos e cierto eje segun segmento completo*/
int segment_axis_compare(Segment* s1, double value, Axis axis)
{
  //Defino el valor minimo y el maximo segun el eje
  double min, max;
  if (axis == X)
  {
    if (s1 -> position1.X < s1 -> position2.X)
    {
      min = s1 -> position1.X;
      max = s1 -> position2.X;
    }
    else
    {
      min = s1 -> position2.X;
      max = s1 -> position1.X;
    }
  }
  else
  {
    if (s1 -> position1.Y < s1 -> position2.Y)
    {
      min = s1 -> position1.Y;
      max = s1 -> position2.Y;
    }
    else
    {
      min = s1 -> position2.Y;
      max = s1 -> position1.Y;
    }
  }
  //Comparo con minimo y maximo
  if (max < value)
  {
    return -1;
  }
  else if (min > value)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
