#pragma once
#include "aabb.h"

/** kdtree de 2 dimensiones de segmentos*/
struct kdtree
{
  /** Arreglo de segmentos (solo si es hoja)*/
  Segment** segments;
  /** Cantidad de segmentos del arreglo*/
  int segment_count;
  /** Hijo izquierdo*/
  struct kdtree* leftson;
  /** Hijo derecho*/
  struct kdtree* rightson;
  /** Bool que iindica si es hoja*/
  bool leaf;
  /** caja contenedora de los segmentos*/
  AABB* box;
};

typedef struct kdtree KDTree;

/* FUNCIONES */

/** Construye recursivamente el kdtree*/
KDTree* kdtree_init(Segment** segments, int segment_count, bool root);

/** Destruye recursivamente el kdtree*/
void kdtree_destroy(KDTree* kdtree);

/** Retorna true ssi el segmento coliciona con algun segmento del kdtree*/
bool kdtree_segment_colition(KDTree* kdtree, Segment* segment);
