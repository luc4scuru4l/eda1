#include "bheap.h"
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
  for(size_t i = aux->capacidad + 1; i <= nuevaCapacidad; i++){
    *(aux->arr + i) = NULL;
  }
  aux->capacidad = nuevaCapacidad; 
}

static void swap(void** ptr1, void** ptr2){
  void* aux = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = aux;
}

static void _bheap_float(BHeap* ptrHeap, size_t flotador){
  BHeap heap = *ptrHeap;
  size_t idxFlotador = flotador;
  size_t idxPadre = idxFlotador / 2;
  while(idxPadre != 0){
    void** padre = heap->arr + idxPadre;
    void** nuevo = heap->arr + idxFlotador;
    if(heap->comp(*padre, *nuevo) >= 0){
      break;
    }
    swap(padre, nuevo);
    idxFlotador = idxPadre;
    idxPadre = idxFlotador / 2;
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
  _bheap_float(heap, aux->ultimo);
}

size_t bheap_capacidad(BHeap heap){
  assert(heap != NULL);
  return heap->capacidad;
}

static void _bheap_sink(BHeap* ptrHeap, size_t toSinkIdx){
  BHeap heap = *ptrHeap;
  size_t raiz = toSinkIdx;
  size_t izq = raiz * 2;
  size_t der = izq + 1;
  while(izq <= heap->ultimo){
    size_t max;
    void** nodoRaiz = heap->arr + raiz;
    void** nodoIzq = heap->arr + izq;
    if(der <= heap->ultimo){
      void** nodoDer = heap->arr + der;
      if(heap->comp(*nodoIzq, *nodoDer) == -1){
        max = der;
      }else{
        max = izq;
      }
    }else{
      max = izq;
    }
    void** nodoMax = heap->arr + max;
    if(heap->comp(*nodoMax, *nodoRaiz) <= 0){
      break;
    }
    swap(nodoRaiz, nodoMax);
    raiz = max;
    izq = raiz * 2;
    der = izq + 1;  
  }
}

void bheap_eliminar(BHeap* ptrHeap, void* dato, FuncionDestructora destr){
  assert(ptrHeap != NULL && *ptrHeap != NULL);
  BHeap heap = *ptrHeap;
  size_t aBorrar = 0;
  for(size_t i = 1; i <= heap->ultimo; i++){
    void* nodo = *(heap->arr + i);
    if(heap->comp(nodo, dato) == 0){
      aBorrar = i;
      break;
    }
  }
  if(aBorrar == 0) // Nada que borrar
    return;
  void** nodoABorrar = heap->arr + aBorrar; 
  if(destr != NULL)
    destr(*nodoABorrar);
  void* ultimo = *(heap->arr + heap->ultimo);
  *(heap->arr + heap->ultimo) = NULL;
  if(aBorrar == heap->ultimo--)
    return;
  *nodoABorrar = ultimo;

  if(aBorrar == 1){
    _bheap_sink(ptrHeap, aBorrar);
    return;
  }

  int comparacion = heap->comp(*nodoABorrar, *(heap->arr + aBorrar / 2));
  if(comparacion > 0){
    _bheap_float(ptrHeap, aBorrar);
  }else{
    _bheap_sink(ptrHeap, aBorrar);
  }
}