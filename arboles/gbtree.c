#include "gbtree.h"
#include "../colas/gcola.h"
#include <stdio.h>
#include <stdlib.h>

GBTree gbtree_crear(){
  return NULL;
}

void gbtree_destruir(GBTree arbol, FuncionDestructora destr){
  if(NULL == arbol){
    return;
  }
  gbtree_destruir(arbol->left, destr);
  gbtree_destruir(arbol->right, destr);

  if(destr != NULL){
    destr(arbol->dato);
  }
  free(arbol);  
}

int gbtree_empty(GBTree arbol){
  return NULL == arbol;
}

GBTree gbtree_unir(void* dato, GBTree left, GBTree right){
  GBTree arbol = malloc(sizeof(struct _GBTree));
  if(NULL == arbol)
    return NULL;
  arbol->dato = dato;
  arbol->left = left;
  arbol->right = right;
  return arbol;
}

GBTree gbtree_unir_entero(int dato, GBTree left, GBTree right){
  int* entero = malloc(sizeof(int));
  if(NULL == entero)
    return NULL;
  *entero = dato;

  return gbtree_unir(entero, left, right);
}

void gbtree_recorrer(GBTree arbol, BTreeOrdenDeRecorrido recorrido, FuncionVisitante visit){
  if(NULL == arbol)
    return;

  if(BTREE_RECORRIDO_PRE == recorrido){
    visit(arbol->dato);
  }
  gbtree_recorrer(arbol->left, recorrido, visit);
  if(BTREE_RECORRIDO_IN == recorrido){
    visit(arbol->dato);
  }
  gbtree_recorrer(arbol->right, recorrido, visit);
  if(BTREE_RECORRIDO_POST == recorrido){
    visit(arbol->dato);
  }
}

int gbtree_nnodos(GBTree arbol){
  if(gbtree_empty(arbol) == 1)
    return 0;
  return 1 + gbtree_nnodos(arbol->left) + gbtree_nnodos(arbol->right);
}

int gbtree_buscar(GBTree arbol, void* dato, FuncionComparadora comp){
  if(NULL == arbol)
    return 0;
  if(comp(arbol->dato, dato) == 0)
    return 1;
  if(gbtree_buscar(arbol->left, dato, comp) == 0){
    return gbtree_buscar(arbol->right, dato, comp);
  } 
  return 1;
}

GBTree gbtree_copiar(GBTree arbol, FuncionCopiadora copy){
  if(gbtree_empty(arbol) == 1)
    return NULL;

  return gbtree_unir(copy(arbol->dato),
                     gbtree_copiar(arbol->left, copy),
                     gbtree_copiar(arbol->right, copy));
}

int gbtree_es_hoja(GBTree arbol){
  if(gbtree_empty(arbol) == 1)
    return 0;
  if(NULL == arbol->left && NULL == arbol->right)
    return 1;
  return 0;
}

int gbtree_altura(GBTree arbol){
  if(gbtree_empty(arbol) == 1)
    return -1;
  if(gbtree_es_hoja(arbol) == 1)
    return 0;
  int altura_izq = 1 + gbtree_altura(arbol->left);
  int altura_der = 1 + gbtree_altura(arbol->right);

  if(altura_izq > altura_der)
    return altura_izq;
  return altura_der;
}

int gbtree_nnodos_profundidad(GBTree arbol, int profundidad){
  if(gbtree_empty(arbol) == 1 || profundidad < 0)
    return 0;
  if(profundidad == 0)
    return 1;
  
  return gbtree_nnodos_profundidad(arbol->left, profundidad - 1) +
         gbtree_nnodos_profundidad(arbol->right, profundidad - 1);
}

int gbtree_profundidad(GBTree arbol, void* dato, FuncionComparadora comp){
  if(gbtree_empty(arbol) == 1)
    return -1;
  if(comp(arbol->dato, dato) == 0){
    return 0;
  }
  int profundidad_izq = gbtree_profundidad(arbol->left, dato, comp);
  if(-1 == profundidad_izq){
    int profundidad_der = gbtree_profundidad(arbol->right, dato, comp);
    if(-1 == profundidad_der)
      return -1;
    return 1 + profundidad_der;
  }
  return 1 + profundidad_izq;
}

void gbtree_recorrer_bfs_i(GBTree arbol, FuncionVisitante visit){
  if(gbtree_empty(arbol) == 1)
    return;
  GCola cola = gcola_crear();
  cola = gcola_encolar(cola, arbol);
  while(gcola_es_vacia(cola) == 0){
    GBTree nodo = (GBTree) gcola_inicio(cola);
    visit(nodo->dato);
    gcola_desencolar(&cola, NULL);
    if(gbtree_empty(nodo->left) == 0)
      cola = gcola_encolar(cola, nodo->left);
    if(gbtree_empty(nodo->right) == 0)
      cola = gcola_encolar(cola, nodo->right);
  }
}