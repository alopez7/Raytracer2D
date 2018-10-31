#pragma once
#include "light.h"
#include "kdtree.h"

/** Struct que contiene luces y segmentos*/
struct scene
{
  /** numero de luces en la escena*/
  int light_count;
  /** arreglo de luces*/
  Light* lights;
  /** kdtree de segmentos*/
  KDTree* kdtree;
  /** alto*/
  int height;
  /** ancho*/
  int withd;
};

typedef struct scene Scene;

/* Funciones */

/** Inicializa la escena */
Scene* scene_init(Light* luces, int light_count, Segment** segments, int segment_count, int height, int withd);

void scene_destroy(Scene* scene);
