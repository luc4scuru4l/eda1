#include "../arboles/gbtree.h"
#include "bstree.h"
#include <stdlib.h>
#include <stdio.h>

BSTree bstree_crear(){
  return gbtree_crear();
}

void bstree_destruir(BSTree arbol, FuncionDestructora destr){
  gbtree_destruir(arbol, destr);
}

int bstree_buscar(BSTree arbol, void* dato, FuncionComparadora comp){
  if(gbtree_empty(arbol))
    return 0;
  int resultado = comp(dato, arbol->dato); 
  if(resultado == 0)
    return 1;
  if(resultado < 0)
    return bstree_buscar(arbol->left, dato, comp);
  return bstree_buscar(arbol->right, dato, comp);
}

BSTree bstree_insertar(BSTree arbol, void * dato, FuncionCopiadora copy, FuncionComparadora comp){
  if(gbtree_empty(arbol)){
    BSTree nuevo = malloc(sizeof(struct _GBTree));
    if(NULL == nuevo){
      puts("Error de asignación de memoria");
      return NULL;
    }
    nuevo->dato = copy(dato);
    nuevo->left = gbtree_crear();
    nuevo->right = gbtree_crear();
    return nuevo;
  }

  int comparacion = comp(dato, arbol->dato);

  if(comparacion < 0)
    arbol->left = bstree_insertar(arbol->left, dato, copy, comp);
  if(comparacion > 0)
    arbol->right = bstree_insertar(arbol->right, dato, copy, comp);
  return arbol;
}

void bstree_recorrer(GBTree arbol, BTreeOrdenDeRecorrido recorrido, FuncionVisitanteExtra visit, void *extra){
  if(gbtree_empty(arbol))
    return;

  if(BTREE_RECORRIDO_PRE == recorrido)
    visit(arbol->dato, extra);

  bstree_recorrer(arbol->left, recorrido, visit, extra);

  if(BTREE_RECORRIDO_IN == recorrido)
    visit(arbol->dato, extra);
  
  bstree_recorrer(arbol->right, recorrido, visit, extra);

  if(BTREE_RECORRIDO_POST == recorrido)
    visit(arbol->dato, extra);
}