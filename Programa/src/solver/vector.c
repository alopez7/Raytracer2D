#include "vector.h"

/** Inicializa un vector */
Vector* vector_init(double x, double y)
{
  Vector* result = malloc(sizeof(Vector));
  result -> X = x;
  result -> Y = y;
  return result;
}

/** Retorna la magnitud del vector*/
double vector_magnitude(Vector * v)
{
  return sqrt(v -> X * v -> X + v -> Y * v -> Y);
}

/** Suma v1 y v2 lo lo guarda en v1*/
void vector_add(Vector* v1, Vector* v2)
{
  v1 -> X += v2 -> X;
  v1 -> Y += v2 -> Y;
}

/** Resta v1 y v2 lo lo guarda en v1*/
void vector_sub(Vector* v1, Vector* v2)
{
  v1 -> X -= v2 -> X;
  v1 -> Y -= v2 -> Y;
}

/** Pondera v por ponderator*/
void vector_scale(Vector* v, double ponderator)
{
  v -> X *= ponderator;
  v -> Y *= ponderator;
}

/** Retorna el producto punto de dos vectores*/
double vector_dot(Vector* v1, Vector* v2)
{
  return v1 -> X * v2 -> X + v1 -> Y * v2 -> Y;
}

/** Retorna un nuevo vector con la suma de los dados*/
Vector* vector_new_add(Vector* v1, Vector* v2)
{
  Vector* result = malloc(sizeof(Vector));
  result -> X = v1 -> X + v2 -> X;
  result -> Y = v1 -> Y + v2 -> Y;
  return result;
}

/** Retorna un nuevo vector con resta de los dados*/
Vector* vector_new_sub(Vector* v1, Vector* v2)
{
  Vector* result = malloc(sizeof(Vector));
  result -> X = v1 -> X - v2 -> X;
  result -> Y = v1 -> Y - v2 -> Y;
  return result;
}

/** Retorna la distancia entre dos puntos (vectores)*/
double vector_distance(Vector* v1, Vector* v2)
{
  return sqrt(pow(v1 -> X - v2 -> X, 2) + pow(v1 -> Y - v2 -> Y, 2));
}


/** Obtiene el valor de la cordenada en el eje especificado */
double vector_get_axis(Vector v, Axis a)
{
  switch(a)
  {
    case X: return v.X;
    case Y: return v.Y;
    default: abort();
  }
}

/** Asigna el valor de la cordenada en el eje especificado */
void vector_set_axis(Vector* v, Axis a, double value)
{
  switch(a)
  {
    case X: v -> X = value; break;
    case Y: v -> Y = value; break;
  }
}

/** Entrega el otro eje */
Axis axis_other(Axis a)
{
  switch(a)
  {
    case X: return Y;
    case Y: return X;
    default: abort();
  }
}
