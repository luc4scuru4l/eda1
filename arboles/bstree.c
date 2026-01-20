#include "../arboles/gbtree.h"
#include "bstree.h"

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

}