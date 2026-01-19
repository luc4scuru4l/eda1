#include <stdlib.h>
#include "glist.h"
#include "../pilas/gstack.h"

GList glist_crear(){
  return NULL;
}

void glist_destruir(GList* lista, FuncionDestructora destr){
  if(lista == NULL || *lista == NULL)
    return;
  for(GNodo* nodo = *lista; nodo != NULL;){
    GNodo* next = nodo->sig;
    destr(nodo->dato);
    free(nodo);
    nodo = next;
  }
  *lista = NULL;
}

GList glist_agregar_inicio(GList lista, void* dato){
  GNodo* nodo = malloc(sizeof(struct _GNodo));
  if(nodo == NULL)
    exit(1);
  nodo->dato = dato;
  nodo->sig = lista;
  return nodo;
}

GList glist_agregar_final(GList lista, void* dato){
  GNodo* nodo = malloc(sizeof(struct _GNodo));
  if(nodo == NULL)
    exit(1);
  nodo->dato = dato;
  nodo->sig = NULL;

  GNodo dummy;
  dummy.sig = lista;
  GNodo* current;
  for(current = &dummy; current->sig != NULL; current = current->sig);
  current->sig = nodo;
  
  return dummy.sig;
}

void glist_recorrer(GList lista, FuncionVisitante visit){
  for(GNodo* nodo = lista; nodo != NULL; nodo = nodo->sig){
    visit(nodo->dato);
  }
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