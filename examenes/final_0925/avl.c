#include "avl.h"
#include <assert.h>

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


void avl_recorrer(AVL arbol, void* extra, FuncionVisitanteExtra visit){
  if(arbol == NULL)
  return;
  avl_recorrer(arbol->izq, extra, visit);
  visit(arbol->dato, extra);
  avl_recorrer(arbol->der, extra, visit);
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

static int _avl_factor_balance(AVL arbol){
  assert(arbol != NULL);
  return avl_altura(arbol->der) - avl_altura(arbol->izq);
}

static void _avl_rotacion_simple_izq(AVL* ptrArbol){
  if(ptrArbol == NULL || *ptrArbol == NULL)
    return;
  AVL arbol = *ptrArbol;
  assert(arbol->der != NULL);
  AVL hijoDerecho = arbol->der;
  arbol->der = hijoDerecho->izq;
  hijoDerecho->izq = arbol;
  arbol->altura = _avl_mayor_altura(arbol->izq, arbol->der) + 1;
  hijoDerecho->altura = _avl_mayor_altura(hijoDerecho->izq, hijoDerecho->der) + 1;
  *ptrArbol = hijoDerecho;
}

static void _avl_rotacion_simple_der(AVL* ptrArbol){
  if(ptrArbol == NULL || *ptrArbol == NULL)
    return;
  AVL arbol = *ptrArbol;
  assert(arbol->izq != NULL);
  AVL hijoIzquierdo = arbol->izq;
  arbol->izq = hijoIzquierdo->der;
  hijoIzquierdo->der = arbol;
  arbol->altura = _avl_mayor_altura(arbol->izq, arbol->der) + 1;
  hijoIzquierdo->altura = _avl_mayor_altura(hijoIzquierdo->izq, hijoIzquierdo->der) + 1;
  *ptrArbol = hijoIzquierdo;
}

static void _avl_nodo_rebalancear(AVL* ptrArbol){
  if(ptrArbol == NULL || *ptrArbol == NULL)
    return;
  AVL arbol = *ptrArbol;
  int balance = _avl_factor_balance(arbol);
  if(balance == 2){ // Se me está cayendo a la derecha
    if(_avl_factor_balance(arbol->der) == -1){
      _avl_rotacion_simple_der(&(arbol->der));
    }
    _avl_rotacion_simple_izq(ptrArbol);
  }else if(balance == -2){ // Se me está cayendo a la izquierda
    if(_avl_factor_balance(arbol->izq) == 1){
      _avl_rotacion_simple_izq(&(arbol->izq));
    }
    _avl_rotacion_simple_der(ptrArbol);
  }
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
  _avl_nodo_rebalancear(ptrArbol);
}

void avl_eliminar(AVL* ptrArbol, void* dato, FuncionComparadora comp, FuncionDestructora destroy){
  if(ptrArbol == NULL || *ptrArbol == NULL)
    return;
  AVL arbol = *ptrArbol;
  int comparacion = comp(dato, arbol->dato);
  if(comparacion < 0){
    avl_eliminar(&(arbol->izq), dato, comp, destroy);
  }else if(comparacion > 0){
    avl_eliminar(&(arbol->der), dato, comp, destroy);
  }else{
    if(arbol->izq != NULL && arbol->der != NULL){ // Es el nodo a eliminar tiene dos hijos
      AVL bigger = arbol->izq;
      while(bigger->der != NULL){
        bigger = bigger->der;
      }
      void* dato = arbol->dato;
      arbol->dato = bigger->dato;
      bigger->dato = dato;
      avl_eliminar(&(arbol->izq), bigger->dato, comp, destroy);
    }else if(arbol->izq == NULL && arbol->der == NULL){ // El nodo a eliminar es una hoja
      avl_destruir(ptrArbol, destroy);
      *ptrArbol = NULL;
      return;
    }else{ // El nodo a eliminar tiene un solo hijo
      AVL target;
      if(arbol->izq != NULL){
        target = arbol->izq;
      }else{
        target = arbol->der;
      }
      arbol->izq = NULL;
      arbol->der = NULL;
      avl_destruir(ptrArbol, destroy);
      *ptrArbol = target;
    }
  }
 
  if(*ptrArbol != NULL){
    (*ptrArbol)->altura = _avl_mayor_altura((*ptrArbol)->izq, (*ptrArbol)->der) + 1;
    _avl_nodo_rebalancear(ptrArbol);
  }
  
}