#pragma once
#include "../libpng/imagelib.h"

/* Es para corregir las tareas */

/** Crea una matriz de tamaño height * width de colores RGB */
void watcher_open(int height, int width);
/** Selecciona un color para las siguientes operaciones de dibujo */
void watcher_set_color(double R, double G, double B);
/** No hace nada */
void watcher_draw_segment(double xi, double yi, double xf, double yf);
/** Pinta el pixel del color seleccionado */
void watcher_paint_pixel(int row, int col);
/** Compara la imagen con el output esperado */
void watcher_snapshot(char* filename);
/** Libera los recursos de la matriz */
void watcher_close();
