#include "watcher.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Image* imagen;
Color color;
float total_diff = 0;
char* filename;

/** Libera la imagen */
void free_image(Image* im)
{
  for (int i = 0; i < im -> height; i++)
  {
    free(im -> pixels[i]);
  }
  free(im -> pixels);
  free(im);
}
/** Crea una matriz de tamaño height * width de colores RGB */
void watcher_open(int height, int width)
{
  imagen = malloc(sizeof(Image));
  imagen -> pixels = malloc(sizeof(Color*) * height);
  for (int i = 0; i < height; i++)
  {
    imagen -> pixels[i] = malloc(sizeof(Color) * width);
    for (int j = 0; j < width; j++)
    {
      imagen -> pixels[i][j].R = 0;
      imagen -> pixels[i][j].G = 0;
      imagen -> pixels[i][j].B = 0;
    }
  }
  imagen -> height = height;
  imagen -> width = width;
}
/** Selecciona un color para las siguientes operaciones de dibujo */
void watcher_set_color(double R, double G, double B)
{
  if (R <= 0) R = 0;
  else if (R >= 1) R = 1;
  if (G <= 0) G = 0;
  else if (G >= 1) G = 1;
  if (B <= 0) B = 0;
  else if (B >= 1) B = 1;
  color.R = R;
  color.G = G;
  color.B = B;
}
/** No hace nada */
void watcher_draw_segment(double xi, double yi, double xf, double yf)
{
  //Holi
}
/** Pinta el pixel del color seleccionado */
void watcher_paint_pixel(int row, int col)
{
  if (row < 0 || row >= imagen -> height) exit(3);
  if (col < 0 || col >= imagen -> width) exit(4);
  imagen -> pixels[row][col].R = color.R;
  imagen -> pixels[row][col].G = color.G;
  imagen -> pixels[row][col].B = color.B;
}
/** No hace nada */
void watcher_snapshot(char* filename)
{
  //Holi
}
/** Escribe la imagen de output y libera los recursos de la matriz */
void watcher_close()
{
  img_png_write_to_file(imagen, "AlumnoOut.png");
  free_image(imagen);
}
