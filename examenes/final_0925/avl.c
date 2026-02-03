#include "avl.h"

AVL avl_crear(){
  return NULL;
}

void avl_destruir(AVL* ptrArbol, FuncionDestructora destroy){
  if(ptrArbol == NULL || *ptrArbol == NULL)
    return;
  AVL arbol = *ptrArbol;
  avl_destruir(&(arbol->izq), destroy);
  avl_destruir(&(arbol->der), destroy);
  if(destroy != NULL)
    destroy(arbol->dato);
  free(arbol);
  *ptrArbol = NULL;
}

int avl_altura(AVL arbol){
  if(arbol == NULL)
    return -1;
  return arbol->altura;
}

static int _avl_mayor_altura(AVL arbol1, AVL arbol2){
  int h1 = avl_altura(arbol1);
  int h2 = avl_altura(arbol2);

  if(h1 > h2)
    return h1;
  return h2;
}

void avl_insertar(AVL* ptrArbol, void* dato, FuncionComparadora comp, FuncionCopiadora copiar){
  assert(ptrArbol != NULL);
  if(*ptrArbol == NULL){
    AVL nodo = malloc(sizeof(struct _AVL));
    nodo->dato = copiar(dato);
    nodo->altura = 0;
    nodo->der = nodo->izq = NULL;
    *ptrArbol = nodo;
    return;
  }
  AVL arbol = *ptrArbol;
  int comparacion = comp(dato, arbol->dato);
  if(comparacion == 0)
    return;
  AVL* target;
  if(comparacion < 0){
    target = &(arbol->izq);
  }else{
    target = &(arbol->der);
  }
  avl_insertar(target, dato, comp, copiar);
  arbol->altura = _avl_mayor_altura(arbol->izq, arbol->der) + 1;
}