#include "scene.h"
#include <stdio.h>

/** Inicializa la escena */
Scene* scene_init(Light* luces, int light_count, Segment** segments, int segment_count, int height, int withd)
{
  Scene* scene= malloc(sizeof(Scene));
  scene -> light_count = light_count;
  scene -> lights = luces;
  printf("Generando el kdtree\n");
  scene -> kdtree = kdtree_init(segments, segment_count, true);
  scene -> height = height;
  scene -> withd = withd;
  return scene;
}


void scene_destroy(Scene* scene)
{
  free(scene -> lights);
  kdtree_destroy(scene -> kdtree);
  free(scene);
}
