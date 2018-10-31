#include <stdio.h>
#include "scene.h"
#include "../watcher/watcher.h"
#include <unistd.h>
#include <string.h>
#include <omp.h>

Scene* parser(char * filename)
{
  //Abro el archivo
  FILE* file = fopen(filename, "r");

  //Leo el tamaño de la escena
  int height;
  int withd;
  fscanf(file, "%i", &height);
  fscanf(file, "%i", &withd);

  watcher_open(height, withd);

  int light_count;
  //Leyendo la cantidad de luces
	fscanf(file, "%i", &light_count);

  Light* luces;
  //Arreglo de luces
  luces = malloc(sizeof(Light) * light_count);


  //Itero sobre todas las luces
  for (int i = 0; i < light_count; i++)
  {
    fscanf(file, "%lf", &luces[i].position.X);
    fscanf(file, "%lf", &luces[i].position.Y);
    fscanf(file, "%lf", &luces[i].color.R);
    fscanf(file, "%lf", &luces[i].color.G);
    fscanf(file, "%lf", &luces[i].color.B);
    fscanf(file, "%lf", &luces[i].intensity);
  }

  //Leo la cantidad de segmento que hay
  int segment_count;
	fscanf(file, "%i", &segment_count);

  //Creo el arreglo de segmentos
  Segment** segments = malloc(sizeof(Segment*) * segment_count);
  for (int i = 0; i < segment_count; i++)
  {
    segments[i] = malloc(sizeof(Segment));
  }

  //Relleno el arreglo
  for (int i = 0; i < segment_count; i++)
  {
    fscanf(file, "%lf", &segments[i] -> position1.X);
    fscanf(file, "%lf", &segments[i] -> position1.Y);
    fscanf(file, "%lf", &segments[i] -> position2.X);
    fscanf(file, "%lf", &segments[i] -> position2.Y);
  }
  fclose(file);

  // watcher_set_color(0.3, 0.3, 0.3);
  //
  // for(int i = 0; i < segment_count; i++)
  // {
  //   Segment* seg = segments[i];
  //   watcher_draw_segment(seg -> position1.X, seg -> position1.Y, seg -> position2.X, seg -> position2.Y);
  // }

  Scene* scene = scene_init(luces, light_count, segments, segment_count, height, withd);


  return scene;
}


int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Dame input\n");
    return 0;
  }
  Scene* scene = parser(argv[1]);
  int len = strlen(argv[1])+1;
  char outstring[len];
  for (int i = 0; i < len; i++)
  {
    outstring[i] = argv[1][i];
  }
  outstring[len - 4] = 'p';
  outstring[len - 3] = 'n';
  outstring[len - 2] = 'g';

  Color*** matrix = malloc(sizeof(Color**) * scene -> height);
  for (int row = 0; row < scene -> height; row++)
  {
    matrix[row] = malloc(sizeof(Color*) * scene -> withd);
    for (int col = 0; col < scene -> withd; col++)
    {
      matrix[row][col] = color_init(0, 0, 0);
    }
  }
  printf("Generando la imagen\n");
  #pragma omp parallel for
  for (int row = 0; row < scene -> height; row++)
  {
    for (int col = 0; col < scene -> withd; col++)
    {
      Color* color = matrix[row][col];
      Vector position;
      position.X = col;
      position.Y = row;
      for (int i = 0; i < scene -> light_count; i++)
      {
        Segment s;
        s.position1 = position;
        s.position2 = scene -> lights[i].position;
        if (!kdtree_segment_colition(scene -> kdtree, &s))
        {
          light_add_color(color, &scene -> lights[i], &position);
        }
      }
      #pragma omp critical
      {
        watcher_set_color(color -> R, color -> G, color -> B);
        watcher_paint_pixel(row, col);
      }
    }
  }

  watcher_snapshot(outstring);
  // watcher_snapshot("scenes/asteroids3.png");

  watcher_close();


  for (int i = 0; i < scene -> height; i++)
  {
    for (int j = 0; j < scene -> withd; j++)
    {
      free(matrix[i][j]);
    }
    free(matrix[i]);
  }
  free(matrix);

  scene_destroy(scene);

  return 0;
}
