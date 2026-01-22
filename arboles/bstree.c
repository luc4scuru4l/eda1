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
  printf("Comparando el %d con el %d: %d\n", *((int*) dato), *((int*) arbol->dato), comparacion);
  if(comparacion < 0){
    return bstree_eliminar(arbol->left, dato, comp, destr);
  }else if(comparacion > 0){
    return bstree_eliminar(arbol->right, dato, comp, destr);
  }
  puts("Encontrado!!!");
  // El nodo a eliminar es una hoja
  if(gbtree_es_hoja(arbol)){
    puts("El nodo a eliminar es una hoja");
    gbtree_destruir(arbol, destr);
    return NULL;
  }

  // El nodo a eliminar tiene dos hijos
  if(arbol->left != NULL && arbol->right != NULL){
    puts("El nodo a eliminar tiene dos hijos");
    GBTree padre_bigger = arbol;
    GBTree bigger = arbol->left;
    while(!gbtree_empty(bigger->right)){
      padre_bigger = bigger;
      bigger = bigger->right;
    }
    printf("El nodo más grande tiene el dato %d\n", *((int*) bigger->dato));
    printf("El padre del nodo más grande tiene el dato %d\n", *((int*) padre_bigger->dato));
    fflush(stdout);

    // El padre del nodo más grande es el nodo a eliminar
    if(padre_bigger == arbol){
      bigger->right = arbol->right;
    }else{
      padre_bigger->right = bigger->left;
      bigger->right = arbol->right;
      bigger->left = arbol->left;
    }

    arbol->left = NULL;
    arbol->right = NULL;
    gbtree_destruir(arbol, destr);

    return bigger;
  }
  puts("El nodo a eliminar tiene solo un hijo");
  //El nodo a eliminar tiene solo un hijo
  GBTree target;  
  if(gbtree_empty(arbol->left)){
    target = arbol->right;
  }else{
    target = arbol->left;
  }

  arbol->left = NULL;
  arbol->right = NULL;

  gbtree_destruir(arbol, destr);

  return target;

}