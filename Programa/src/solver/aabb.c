#include "aabb.h"
#include "../watcher/watcher.h"

/** Inicializa el bounding box*/
AABB* aabb_init(Segment** segments, int segment_count)
{
  //Reservo memoria
  AABB* aabb = malloc(sizeof(AABB));

  //Creo un minimo y un maximo para mejorarlos
  aabb -> min_point = vector_init(INFINITY, INFINITY);
  aabb -> max_point = vector_init(-INFINITY, -INFINITY);

  //Itero sobre los segmentos y mejoro el minimo y el maximo
  for (int i = 0; i < segment_count; i++)
  {
    Segment* seg = segments[i];

    aabb -> min_point -> X = fmin(aabb -> min_point -> X, fmin(seg -> position1.X, seg -> position2.X));
    aabb -> min_point -> Y = fmin(aabb -> min_point -> Y, fmin(seg -> position1.Y, seg -> position2.Y));
    aabb -> max_point -> X = fmax(aabb -> max_point -> X, fmax(seg -> position1.X, seg -> position2.X));
    aabb -> max_point -> Y = fmax(aabb -> max_point -> Y, fmax(seg -> position1.Y, seg -> position2.Y));
  }
  return aabb;
}

/** Destruye el aabb*/
void aabb_destroy(AABB* aabb)
{
  free(aabb -> max_point);
  free(aabb -> min_point);
  free(aabb);
}

/** Dibuja la caja con el warcher y el color depende de si es hoja*/
void aabb_draw(AABB* box, bool leaf)
{
  if (leaf)
  {
    watcher_set_color(0, 1, 0);
  }
  else
  {
    watcher_set_color(1, 1, 0);
  }
  watcher_draw_segment(box -> min_point -> X, box -> min_point -> Y, box -> min_point -> X, box -> max_point -> Y);
  watcher_draw_segment(box -> min_point -> X, box -> min_point -> Y, box -> max_point -> X, box -> min_point -> Y);
  watcher_draw_segment(box -> max_point -> X, box -> min_point -> Y, box -> max_point -> X, box -> max_point -> Y);
  watcher_draw_segment(box -> min_point -> X, box -> max_point -> Y, box -> max_point -> X, box -> max_point -> Y);
  // watcher_draw_segment(box -> min_point -> X, box -> min_point -> Y, box -> max_point -> X, box -> max_point -> Y);
}

/** Retorna true ssi el segmento coliciona con la caja */
bool aabb_segment_colition(AABB* box, Segment* segment)
{
  //obtengo los valores minimos y maximos del segmento
  double minx = fmin(segment -> position1.X, segment -> position2.X);
  double maxx = fmax(segment -> position1.X, segment -> position2.X);

  double miny = fmin(segment -> position1.Y, segment -> position2.Y);
  double maxy = fmax(segment -> position1.Y, segment -> position2.Y);
  //
  // double minx, miny, maxx, maxy;
  // if (segment -> position1.X <= segment -> position2.X)
  // {
  //   minx = segment -> position1.X;
  //   maxx = segment -> position2.X;
  // }
  // else
  // {
  //   minx = segment -> position2.X;
  //   maxx = segment -> position1.X;
  // }
  // if (segment -> position1.Y <= segment -> position2.Y)
  // {
  //   miny = segment -> position1.Y;
  //   maxy = segment -> position2.Y;
  // }
  // else
  // {
  //   miny = segment -> position2.Y;
  //   maxy = segment -> position1.Y;
  // }
  //Si no hay colision de cajas retorno false
  if (minx > box -> max_point -> X) return false;
  if (miny > box -> max_point -> Y) return false;
  if (maxx < box -> min_point -> X) return false;
  if (maxy < box -> min_point -> Y) return false;
  //Veo si hay algun punto del segmento contenido en la caja
  if (segment -> position1.X <= box -> max_point -> X && segment -> position1.X >= box -> min_point -> X)
  {
    if (segment -> position1.Y <= box -> max_point -> Y && segment -> position1.Y >= box -> min_point -> Y)
    {
      return true;
    }
  }
  if (segment -> position2.X <= box -> max_point -> X && segment -> position2.X >= box -> min_point -> X)
  {
    if (segment -> position2.Y <= box -> max_point -> Y && segment -> position2.Y >= box -> min_point -> Y)
    {
      return true;
    }
  }
  //Pruebo el segmento con los segmento de la caja
  Vector p1, p2, p3, p4;
  p1.X = box -> min_point -> X;
  p1.Y = box -> min_point -> Y;
  p2.X = box -> max_point -> X;
  p2.Y = box -> min_point -> Y;
  p3.X = box -> max_point -> X;
  p3.Y = box -> max_point -> Y;
  p4.X = box -> min_point -> X;
  p4.Y = box -> max_point -> Y;
  Segment s1, s2, s3, s4;
  s1.position1 = p1;
  s1.position2 = p2;
  s2.position1 = p2;
  s2.position2 = p3;
  s3.position1 = p3;
  s3.position2 = p4;
  s4.position1 = p4;
  s4.position2 = p1;
  if (segment_segment_colition(segment, &s1)) return true;
  if (segment_segment_colition(segment, &s2)) return true;
  if (segment_segment_colition(segment, &s3)) return true;
  if (segment_segment_colition(segment, &s4)) return true;

  return false;
}
