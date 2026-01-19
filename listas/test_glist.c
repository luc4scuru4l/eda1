#include <stdio.h>
#include <stdlib.h>
#include "glist.h"

static void glist_imprimir(void* dato){
  printf("%d ", *((int*) dato));
}

static void destruir_entero(void* dato){
  free((int*) dato);
}

int main(){
  int* dato1 = malloc(sizeof(int));
  *dato1 = 1;
  int* dato2 = malloc(sizeof(int));
  *dato2 = 2;
  int* dato3 = malloc(sizeof(int));
  *dato3 = 3;
  int* dato4 = malloc(sizeof(int));
  *dato4 = 4;

  GList lista = glist_crear();
  lista = glist_agregar_final(lista, dato3);
  lista = glist_agregar_final(lista, dato2);
  lista = glist_agregar_final(lista, dato1);
  lista = glist_agregar_inicio(lista, dato4);
  glist_recorrer(lista, glist_imprimir);
  puts("");

  glist_destruir(&lista, destruir_entero);

  return 0;
}