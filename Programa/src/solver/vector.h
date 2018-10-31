#pragma once
#include <stdlib.h>
#include <math.h>

enum axis
{
  X,
  Y
};

typedef enum axis Axis;

/** Struct que contiene un vector de 3 dimensiones*/
struct vector
{
    /** Coordenada X */
    double X;
    /** Coordenada Y */
    double Y;
};

typedef struct vector Vector;

/* Funciones */

/** Entrega el otro eje */
Axis axis_other(Axis a);

/** Inicializa un vector */
Vector* vector_init(double x, double y);

/** Retorna la magnitud del vector*/
double vector_magnitude(Vector * v);

/** Suma v1 y v2 lo lo guarda en v1*/
void vector_add(Vector* v1, Vector* v2);

/** Resta v1 y v2 lo lo guarda en v1*/
void vector_sub(Vector* v1, Vector* v2);

/** Pondera v por ponderator*/
void vector_scale(Vector* v, double ponderator);

/** Retorna el producto punto de dos vectores*/
double vector_dot(Vector* v1, Vector* v2);

/** Retorna un nuevo vector con la suma de los dados*/
Vector* vector_new_add(Vector* v1, Vector* v2);

/** Retorna un nuevo vector con resta de los dados*/
Vector* vector_new_sub(Vector* v1, Vector* v2);

/** Retorna la distancia entre dos puntos (vectores)*/
double vector_distance(Vector* v1, Vector* v2);

/** Obtiene el valor de la cordenada en el eje especificado */
double vector_get_axis(Vector v, Axis a);

/** Asigna el valor de la cordenada en el eje especificado */
void vector_set_axis(Vector* v, Axis a, double value);
