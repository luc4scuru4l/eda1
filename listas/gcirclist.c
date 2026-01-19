#include <stdio.h>
#include <stdlib.h>
#include "glist.h"
#include "../pilas/gstack.h"

GList glist_crear(){
  return NULL;
}

void glist_destruir(GList* lista, FuncionDestructora destr){
  if(lista == NULL || *lista == NULL)
    return;
  
  GNodo* primero = (*lista)->sig;
  (*lista)->sig = NULL;

  for(GNodo* nodo = primero; nodo != NULL;){
    GNodo* siguiente = nodo->sig;
    if(destr != NULL) destr(nodo->dato);
    free(nodo);
    nodo = siguiente;
  }
  *lista = NULL;
}

GList glist_agregar_inicio(GList lista, void* dato){
  GNodo* nodo = malloc(sizeof(struct _GNodo));
  if(nodo == NULL){
    puts("Error en la asignación de memoria al crear un nuevo nodo.");
    exit(1);
  }
  nodo->dato = dato;
  if(lista == NULL){
    nodo->sig = nodo;
    return nodo;
  }
  nodo->sig = lista->sig;
  lista->sig = nodo;
  
  return lista;
}

GList glist_agregar_final(GList lista, void* dato){
  GNodo* nodo = malloc(sizeof(struct _GNodo));
  if(nodo == NULL){
    puts("Error en la asignación de memoria al crear un nuevo nodo.");
    exit(1);
  }
  nodo->dato = dato;
  if(lista == NULL){
    nodo->sig = nodo;
    return nodo;
  }
  nodo->sig = lista->sig;
  lista->sig = nodo;
  return nodo;
}

void glist_recorrer(GList lista, FuncionVisitante visit){
  if(NULL == lista)
    return;
  GNodo* current = lista->sig;
  do {
    visit(current->dato);
    current = current->sig;
  }while(current != lista->sig);
}

GList glist_invertir(GList lista){
  if(lista == NULL || lista->sig == NULL)
    return lista;
  
  Pila pila = pila_crear();
  for(GNodo* nodo = lista; nodo != NULL; nodo = nodo->sig){
    pila = pila_apilar(pila, nodo);
  }
  GNodo* first = (GNodo *) pila_tope(pila);
  pila = pila_desapilar(pila, NULL);
  GNodo* current = first;

  while(!pila_es_vacia(pila)){
    current->sig = (GNodo *) pila_tope(pila);
    pila = pila_desapilar(pila, NULL);
    current = current->sig;
  }

  current->sig = NULL;

  return first;
}

void* glist_obtener_primero(GList lista){
  if(NULL == lista)
    return NULL;
  return lista->sig->dato;
}

void glist_eliminar_primero(GList* lista, FuncionDestructora destr){
  if(NULL == lista || NULL == *lista)
    return;
  GNodo* primero = (*lista)->sig;
  (*lista)->sig = primero->sig;
  primero->sig = NULL;
  if(NULL != destr)
    destr(primero->dato);
  
  if(primero == *lista){
    free(primero);
    *lista = NULL;
  }else{
    free(primero);
  }
}