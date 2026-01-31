#include <stdio.h>
#include <assert.h>
#include "bheap.h"

static int comparar_enteros(void* a, void* b){
  return *((int*) a) - *((int*) b) ; 
}

static void* copiar_entero(void* dato){
  int* a = malloc(sizeof(int));
  assert(a != NULL);
  *a = *((int*) dato);
  return a; 
}

static void imprimir_entero(void* dato, __attribute__((unused)) void* extra){
  printf("%d ", *((int*) dato)); 
}

static void destruir_entero(void* dato){
  if(dato != NULL)
    free((int*) dato);
}

int main(){
  int numeros[] = {10, 20, 15, 25, 30, 16, 18, 19};
  size_t cantNumeros = sizeof(numeros) / sizeof(int);
  
  BHeap heap1 = bheap_crear(cantNumeros, comparar_enteros);
  for(size_t i = 0; i < cantNumeros; i++){
    bheap_insertar(&heap1, numeros + i, copiar_entero);
  }

  bheap_recorrer(heap1, NULL, imprimir_entero);
  puts("");

  int toAdd = 22;
  printf("Ahora quiero añadir el elemento %d\n", toAdd);
  
  bheap_insertar(&heap1, &toAdd, copiar_entero);
  
  assert(heap1->capacidad == cantNumeros * 2);
  
  bheap_recorrer(heap1, NULL, imprimir_entero);
  puts("");
  
  int toDelete = 16;
  printf("Ahora quiero eliminar el elemento %d\n", toDelete);
  bheap_eliminar(&heap1, &toDelete, destruir_entero);
  bheap_recorrer(heap1, NULL, imprimir_entero);
  puts("");
  
  int toDelete2 = 30;
  printf("Ahora quiero eliminar el primer elemento, es decir el %d\n", toDelete2);
  bheap_eliminar(&heap1, &toDelete2, destruir_entero);
  bheap_recorrer(heap1, NULL, imprimir_entero);
  puts("");

  int toDelete3 = 18;
  printf("Ahora quiero eliminar el ultimo elemento, es decir, el %d\n", toDelete3);
  bheap_eliminar(&heap1, &toDelete3, destruir_entero);
  bheap_recorrer(heap1, NULL, imprimir_entero);
  puts("");
  
  bheap_destruir(&heap1, destruir_entero);
  
  puts("Ahora voy a crear un heap a partir de un array con los numeros del 0 al 19");
  void** otrosNumeros = malloc(sizeof(void*) * 20);
  for(int i = 0; i < 20; i++){
    int* aux = malloc(sizeof(int));
    *aux = i;
    otrosNumeros[i] = aux;
  }
  BHeap heap2 = bheap_crear_desde_arr(otrosNumeros, 20, copiar_entero, comparar_enteros);
  bheap_recorrer(heap2, NULL, imprimir_entero);
  puts("");
  
  bheap_destruir(&heap2, destruir_entero);

  for(int i = 0; i < 20; i++){
    free((int*) otrosNumeros[i]);
  }
  free(otrosNumeros);

  puts("Todo ok");

  return 0;
}