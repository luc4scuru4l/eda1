#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "gbtree.h"

void imprimir_entero(void* dato){
  int entero = *((int*) dato);
  printf("%d ", entero);
}

void destruir_entero(void* dato){
  free((int*) dato);
}

int comparar_enteros(void* dato, void* dato2){
  int a = *((int*) dato);
  int b = *((int*) dato2);

  if (a < b)
    return -1;
  if(a > b)
    return 1;
  return 0;
}

void* copiar_entero(void* dato){
  int* entero = malloc(sizeof(int));
  // Ya se que esto no está del todo bien, ignoremoslo por ahora.
  if(NULL == entero)
    return NULL;
  *entero = *((int*) dato);
  return entero;
}

int main() {

  GBTree lll = gbtree_unir_entero(0, gbtree_crear(), gbtree_crear());
  GBTree ll = gbtree_unir_entero(1, lll, gbtree_crear());
  GBTree l = gbtree_unir_entero(2, ll, gbtree_crear());
  GBTree r = gbtree_unir_entero(3, gbtree_crear(), gbtree_crear());
  GBTree raiz = gbtree_unir_entero(4, l, r);

  gbtree_recorrer(raiz, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");

  int aBuscar1 = 1;
  int aBuscar5 = 5;

  assert(gbtree_nnodos(raiz) == 5);
  assert(gbtree_buscar(raiz, &aBuscar1, comparar_enteros) == 1);
  assert(gbtree_buscar(raiz, &aBuscar5, comparar_enteros) == 0);

  GBTree raizCopia = gbtree_copiar(raiz, copiar_entero);

  assert(gbtree_altura(raiz) == 3);
  assert(gbtree_altura(ll) == 1);
  assert(gbtree_altura(lll) == 0);
  assert(gbtree_altura(gbtree_crear()) == -1);

  gbtree_destruir(raiz, destruir_entero);
  gbtree_destruir(raizCopia, destruir_entero);

  puts("Yay!!");

  return 0;
}