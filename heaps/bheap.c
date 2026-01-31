#include "bheap.h"
#include <math.h>
#include <assert.h>

BHeap bheap_crear(size_t capacidad, FuncionComparadora comp){
  assert(comp != NULL);
  assert(capacidad > 0);

  BHeap heap = malloc(sizeof(struct _BHeap));
  assert(heap != NULL);

  heap->arr = malloc(sizeof(void*) * (capacidad + 1));
  assert(heap->arr != NULL);

  for(size_t i = 0; i < capacidad + 1; i++){
    *(heap->arr + i) = NULL;
  }

  heap->capacidad = capacidad;
  heap->ultimo = 0;
  heap->comp = comp;

  return heap;
}

void bheap_destruir(BHeap* heap, FuncionDestructora destr){
  assert(heap != NULL && *heap != NULL);
  if(destr != NULL){
    void** data = (*heap)->arr;
    for(size_t i = 1; i <= (*heap)->ultimo; i++){
      if(*(data + i) != NULL){
        destr(*(data + i));
      }
    }
  }
  free((*heap)->arr);
  free(*heap);
  *heap = NULL;
}

int bheap_es_vacio(BHeap heap){
  assert(heap != NULL);
  return heap->ultimo == 0;
}

void bheap_recorrer(BHeap heap, void* extra, FuncionVisitante visit){
  assert(heap != NULL);
  if(bheap_es_vacio(heap))
    return;
  
  for(size_t i = 1; i <= heap->ultimo; i++){
    visit(*(heap->arr + i), extra);
  }
}

static void _bheap_agrandar(BHeap* heap){
  BHeap aux = *heap;
  size_t nuevaCapacidad = 2 * aux->capacidad;
  aux->arr = realloc(aux->arr, sizeof(void*) * (nuevaCapacidad + 1));
  assert(aux->arr != NULL);
  for(size_t i = aux->capacidad + 1; i < nuevaCapacidad; i++){
    *(aux->arr + i) = NULL;
  }
  aux->capacidad = nuevaCapacidad; 
}

static void swap(void** ptr1, void** ptr2){
  void* aux = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = aux;
}

static void _bheap_float(BHeap* ptrHeap){
  BHeap heap = *ptrHeap;
  size_t idxFlotador = heap->ultimo;
  size_t idxPadre = floor(idxFlotador / 2);
  while(idxPadre != 0){
    void** padre = heap->arr + idxPadre;
    void** nuevo = heap->arr + idxFlotador;
    if(heap->comp(*padre, *nuevo) >= 0){
      break;
    }
    swap(padre, nuevo);
    idxFlotador = idxPadre;
    idxPadre = floor(idxFlotador / 2);
  }
}

void bheap_insertar(BHeap* heap, void* dato, FuncionCopiadora copy){
  assert(heap != NULL && *heap != NULL);
  BHeap aux = *heap;
  if((aux->ultimo + 1 > aux->capacidad)){
    _bheap_agrandar(heap);
  }
  aux->ultimo++;
  *(aux->arr + aux->ultimo) = copy(dato);
  _bheap_float(heap);
}

