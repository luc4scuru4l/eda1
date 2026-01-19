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
  gbtree_destruir(raizCopia, destruir_entero);
  
  assert(gbtree_altura(raiz) == 3);
  assert(gbtree_altura(ll) == 1);
  assert(gbtree_altura(lll) == 0);
  assert(gbtree_altura(gbtree_crear()) == -1);
  
  gbtree_destruir(raiz, destruir_entero);
  
  
  GBTree nodo13 = gbtree_unir_entero(13, gbtree_crear(), gbtree_crear());
  GBTree nodo14 = gbtree_unir_entero(14, nodo13, gbtree_crear());
  GBTree nodo6 = gbtree_unir_entero(6, gbtree_crear(), gbtree_crear());
  GBTree nodo9 = gbtree_unir_entero(9, nodo6, nodo14);
  
  GBTree nodo72 = gbtree_unir_entero(72, gbtree_crear(), gbtree_crear());
  GBTree nodo26 = gbtree_unir_entero(26, gbtree_crear(), gbtree_crear());
  GBTree nodo64 = gbtree_unir_entero(64, nodo26, nodo72);
  
  GBTree nodo17 = gbtree_unir_entero(17, gbtree_crear(), gbtree_crear());
  
  GBTree nodo20 = gbtree_unir_entero(20, nodo17, nodo64);
  
  GBTree nodo15 = gbtree_unir_entero(15, nodo9, nodo20);
  
  gbtree_recorrer(nodo15, BTREE_RECORRIDO_IN, imprimir_entero);
  puts("");

  gbtree_recorrer_bfs_i(nodo15, imprimir_entero);
  puts("");
  
  gbtree_destruir(nodo15, destruir_entero);
  
  puts("Yay!!");

  return 0;
}