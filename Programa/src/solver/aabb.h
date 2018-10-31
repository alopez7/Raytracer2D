#pragma once
#include "segment.h"

/** Define las dimensiones de una caja en 2 dimensiones*/
struct aabb
{
  /** Punto maximo*/
  Vector* max_point;
  /** Punto minimo*/
  Vector* min_point;
};

typedef struct aabb AABB;

/* FUNCIONES */

/** Inicializa el bounding box*/
AABB* aabb_init(Segment** segments, int segment_count);

/** Destruye el aabb*/
void aabb_destroy(AABB* aabb);

/** Dibuja la caja con el warcher y el color depende de si es hoja*/
void aabb_draw(AABB* box, bool leaf);

/** Retorna true ssi el segmento coliciona con la caja */
bool aabb_segment_colition(AABB* box, Segment* segment);
