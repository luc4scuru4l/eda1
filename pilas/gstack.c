#include <stdio.h>
#include "gstack.h"

Pila pila_crear(){
  return NULL;
}

void pila_destruir(Pila* pila, FuncionDestructora destr){
  glist_destruir(pila, destr);
}

int pila_es_vacia(Pila pila){
  if(pila == NULL)
    return 1;
  return 0;
}

void* pila_tope(Pila pila){
  if(pila_es_vacia(pila))
    return NULL;
  return pila->dato;
}

Pila pila_apilar(Pila pila, void* dato){
  return glist_agregar_inicio(pila, dato);
}

Pila pila_desapilar(Pila pila, FuncionDestructora destr){
  if(pila_es_vacia(pila))
    return pila;
  Pila aux = pila->sig;
  pila->sig = NULL;
  glist_destruir(&pila, destr);
  return aux;
}