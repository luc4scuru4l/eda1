#include "../arboles/gbtree.h"
#include "../pilas/gstack.h"
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

BSTree bstree_eliminar(BSTree arbol, void *dato, FuncionComparadora comp, FuncionDestructora destr){
  if(gbtree_empty(arbol))
    return NULL;
  
  int comparacion = comp(dato, arbol->dato);

  if(comparacion < 0){
    return bstree_eliminar(arbol->left, dato, comp, destr);
  }else if(comparacion > 0){
    return bstree_eliminar(arbol->right, dato, comp, destr);
  }

  // El nodo a eliminar es una hoja
  if(gbtree_es_hoja(arbol)){
    gbtree_destruir(arbol, destr);
    return NULL;
  }

  // El nodo a eliminar tiene dos hijos
  if(arbol->left != NULL && arbol->right != NULL){
    Pila stack = pila_crear(); 
    GBTree bigger = arbol->left;
    stack = pila_apilar(stack, bigger);
    while(bigger->right != NULL){
      stack = pila_apilar(stack, bigger->right);
      bigger = bigger->right;
    }
    GBTree last = pila_tope(stack);
    
  }

  BSTree target;
  if(gbtree_empty(arbol->left)){
    target = arbol->right;
  }

  target = arbol->left;
}