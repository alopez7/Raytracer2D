#include "kdtree.h"
#include <stdio.h>
#include "../watcher/watcher.h"
#include <unistd.h>

int STOP_DIVIDING = 200;

/** Cambia de posicion el segmento de la posicion i con el de la posicion k*/
void swap(Segment** segments, int i, int k)
{
  Segment* aux = segments[i];
  segments[i] = segments[k];
  segments[k] = aux;
}

/** Particiona un arreglo de segmentos en mayores y menores que un cierto pivote*/
int partition(Segment** segments, int start, int end, Axis axis)
{
  Segment* pivot = segments[end];
  //Posicion anterior al primer mayor al pivote
  int i = start - 1;
  for (int k = start; k < end; k++)
  {
    int cmp = segment_centre_compare(segments[k], pivot, axis);
    if (cmp <= 0)
    {
      swap(segments, i+1, k);
      i++;
    }
  }
  swap(segments, i+1, end);
  return i+1;
}

/** Encuentra la mediana de un arreglo de segmentos*/
Segment* quick_select(Segment** segments, int start, int end, int target, Axis axis)
{
  int pivot = partition(segments, start, end, axis);
  if (pivot == target)
  {
    return segments[target];
  }
  else if (pivot < target)
  {
    return quick_select(segments, pivot + 1, end, target, axis);
  }
  else
  {
    return quick_select(segments, start, pivot - 1, target, axis);
  }
}

/** COnstruye recursivamente el kdtree*/
KDTree* kdtree_init(Segment** segments, int segment_count, bool root)
{
  //Reservo la memoria
  KDTree* kd = malloc(sizeof(KDTree));

  //Calculo la bounding box
  kd -> box = aabb_init(segments, segment_count);
  // aabb_draw(kd -> box, segment_count < STOP_DIVIDING);
  // usleep(100000);

  //Si tengo que dejar de dividir
  if (segment_count < STOP_DIVIDING)
  {
    //Iniciailizo todos sus elementos como hoja
    kd -> leaf = true;
    kd -> leftson = NULL;
    kd -> rightson = NULL;
    kd -> segment_count = segment_count;
    kd -> segments = segments;
    return kd;
  }
  //Si no es hoja
  else
  {
    //pongo sus variables de no hoja
    kd -> leaf = false;
    kd -> segments = NULL;
    kd -> segment_count = 0;

    //Calculo el eje más largo para dividir
    float diff_x = kd -> box -> max_point -> X - kd -> box -> min_point -> X;
    float diff_y = kd -> box -> max_point -> Y - kd -> box -> min_point -> Y;
    Axis axis;
    if (diff_x > diff_y)
    {
      axis = X;
    }
    else
    {
      axis = Y;
    }

    //Calculo la mediana en el eje más largo
    Segment* median = quick_select(segments, 0, segment_count - 1, segment_count / 2, axis);
    //Calculo el valor en el eje donde se divide
    double divition = axis == X ? (median -> position1.X + median -> position2.X) / 2 : (median -> position1.Y + median -> position2.Y) / 2;

    //En caso de ser par encuentro la otra mediana
    if (segment_count % 2 == 0)
    {
      Segment* other_median = quick_select(segments, 0, segment_count / 2 - 1, segment_count / 2 - 1, axis);
      double other_divition = axis == X ? (other_median -> position1.X + other_median -> position2.X) / 2 : (other_median -> position1.Y + other_median -> position2.Y) / 2;
      divition = (divition + other_divition) / 2;
    }


    //Calculo cuantos segmentos hay a cada lado (hay segmentos que estan en ambos)
    int count_less = 0;
    int count_more = 0;
    for (int seg = 0; seg < segment_count; seg++)
    {
      int cmp = segment_axis_compare(segments[seg], divition, axis);
      if (cmp <= 0)
      {
        count_less++;
      }
      if (cmp >= 0)
      {
        count_more++;
      }
    }

    //Creo los arreglos de segmentos de los hijos
    Segment** seg_left = malloc(sizeof(Segment*) * count_less);
    Segment** seg_right = malloc(sizeof(Segment*) * count_more);

    //Traspaso los datos a los arreglos
    int left_count = 0;
    int right_count = 0;
    for (int seg = 0; seg < segment_count; seg++)
    {
      int cmp = segment_axis_compare(segments[seg], divition, axis);
      if (cmp < 0)
      {
        seg_left[left_count] = segments[seg];
        left_count++;
      }
      else if (cmp > 0)
      {
        seg_right[right_count] = segments[seg];
        right_count++;
      }
      else
      {
        // Obtengo el segmento
        Segment* segment = segments[seg];

        // Si el vector es paralelo al eje, se mete a ambas cajas
        if(vector_get_axis(segment -> position1,axis) == vector_get_axis(segment -> position2,axis))
        {
          seg_left[left_count] = segment;
          left_count++;
          Segment* new_segment = malloc(sizeof(Segment));
          new_segment -> position1 = segment -> position1;
          new_segment -> position2 = segment -> position2;
          seg_right[right_count] = new_segment;
          right_count++;
        }
        else
        {
          // Calculo el punto de la division por el eje
          double t = (divition - vector_get_axis(segment -> position1,axis))/(vector_get_axis(segment -> position2,axis) - vector_get_axis(segment -> position1,axis));
          // Interpolo el valor de la otra dimension segun ese punto
          double new_coord = t * vector_get_axis(segment -> position2,axis_other(axis)) + (1-t) * vector_get_axis(segment -> position1,axis_other(axis));

          // Si el p1 es mayor a p2 en este eje, los invierto
          if(vector_get_axis(segment -> position1,axis) > vector_get_axis(segment -> position2,axis))
          {
            Vector aux = segment -> position1;
            segment -> position1 = segment -> position2;
            segment -> position2 = aux;
          }

          // p1 < p2 en este eje, garantizado
          Segment* minor = malloc(sizeof(Segment));
          // Segmento de p1 a pN
          minor -> position1 = segment -> position1;
          vector_set_axis(&minor -> position2, axis, divition);
          vector_set_axis(&minor -> position2, axis_other(axis), new_coord);

          seg_left[left_count] = minor;
          left_count++;

          Segment* mayor = malloc(sizeof(Segment));
          // Segmento de p2 a pN
          mayor -> position1 = segment -> position2;
          vector_set_axis(&mayor -> position2, axis, divition);
          vector_set_axis(&mayor -> position2, axis_other(axis), new_coord);

          seg_right[right_count] = mayor;
          right_count++;

          free(segment);
        }
      }
    }

    //Creo a los hijos
    kd -> leftson = kdtree_init(seg_left, left_count, false);
    kd -> rightson = kdtree_init(seg_right, right_count, false);

    //Libero el arreglo de segmentos propio si no soy root

    free(segments);


    //Retorno el kd
    return kd;
  }
}

/** Destruye recursivamente el kdtree*/
void kdtree_destroy(KDTree* kdtree)
{
  if (kdtree -> leaf)
  {
    for (int i = 0; i < kdtree -> segment_count; i++)
    {
      free(kdtree -> segments[i]);
    }
    free(kdtree -> segments);
  }
  else
  {
    kdtree_destroy(kdtree -> leftson);
    kdtree_destroy(kdtree -> rightson);
  }
  aabb_destroy(kdtree -> box);
  free(kdtree);
}

/** Retorna true ssi el segmento coliciona con algun segmento del kdtree*/
bool kdtree_segment_colition(KDTree* kdtree, Segment* segment)
{
  //Si no coliciona con la caja, retorno false
  if (!aabb_segment_colition(kdtree -> box, segment)) return false;
  //Si es una hoja, coliciono segmentos con segmentos
  if (kdtree -> leaf)
  {
    for (int i = 0; i < kdtree -> segment_count; i++)
    {
      //Si un segmento coliciona, retoeno true
      if (segment_segment_colition(segment, kdtree -> segments[i]))
      {
        return true;
      }
    }
    //Si ninguno coliciona retorno false
    return false;
  }
  //Si no es una hoja
  else
  {
    //Si el segmento coliciona con elgun segmento de mi kdtree izquierdo retorno true
    if (kdtree_segment_colition(kdtree -> leftson, segment))
    {
      return true;
    }
    //Sino, reviso si coliciona con algun segmento del kdtree derecho
    return kdtree_segment_colition(kdtree -> rightson, segment);
  }
}
