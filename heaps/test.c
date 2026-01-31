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

  puts("Todo ok");

  return 0;
}