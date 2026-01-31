#ifndef __B_HEAP__
#define __B_HEAP__
#include <stdlib.h>

typedef void (*FuncionVisitante)(void*, void*);
typedef int (*FuncionComparadora)(void*, void*);
typedef void (*FuncionDestructora)(void*);
typedef void* (*FuncionCopiadora)(void*);

typedef struct _BHeap {
  void** arr;
  size_t capacidad;
  size_t ultimo;
  FuncionComparadora comp;
} *BHeap;

/**
 * Crea un heap vacío.
 * Dejamos la posición 0 del array vacía para simplificar calculos.
 */
BHeap bheap_crear(size_t capacidad, FuncionComparadora comp);

/**
 * Destruye un heap.
 */
void bheap_destruir(BHeap* heap, FuncionDestructora destr);

/**
 * Retorna 1 si el heap está vacío. 0 en caso contrario.
 */
int bheap_es_vacio(BHeap heap);

/**
 * Recorre un heap utilizando BFS.
 */
void bheap_recorrer(BHeap heap, void* extra, FuncionVisitante visit);

/**
 * Inserta una copia del dato en el heap. 
 */
void bheap_insertar(BHeap* heap, void* dato, FuncionCopiadora copy);

/**
 * Retorna la capacidad del heap.
 */
size_t bheap_capacidad(BHeap heap);

#endif