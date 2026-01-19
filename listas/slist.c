#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

size_t slist_longitud(SList lista){
  size_t size = 0;
  for(SNodo* current = lista; current != NULL; current = current->sig)
    size++;
  return size;
}

void slist_concatenar(SList l1, SList l2){
  if(slist_vacia(l1) || slist_vacia(l2))
    return;
  for(SNodo* current = l2; current != NULL; current = current->sig)
    slist_agregar_final(l1, current->dato);
}

SList slist_insertar(SList lista, size_t pos, int dato){
  if(pos == 0)
    return slist_agregar_inicio(lista, dato);
  
  SNodo* current;
  size_t counter = 0;
  for(current = lista; current != NULL; current = current->sig){
    if(counter++ == pos - 1) break;
  }

  SNodo* aux = current->sig;
  current->sig = NULL;
  slist_agregar_final(current, dato);
  current->sig->sig = aux;

  return lista;
}

SList slist_eliminar(SList lista, size_t pos){
  if(pos == 0){
    SNodo* aux = lista->sig;
    lista->sig = NULL;
    slist_destruir(lista);
    return aux;  
  }
  SNodo* nodo = lista;
  size_t counter;
  size_t idx = slist_longitud(lista);
  if(pos >= idx){
    idx -= 1;
  }else{
    idx = pos;
  }
  for(counter = 0; nodo != NULL && counter++ < idx - 1; nodo = nodo->sig);
  SNodo* nodoAEliminar = nodo->sig;
  nodo->sig = nodoAEliminar->sig;
  nodoAEliminar->sig = NULL;
  slist_destruir(nodoAEliminar);
  return lista;
}

int slist_contiene(SList lista, int dato){
  for(SNodo* nodo = lista; nodo != NULL; nodo = nodo->sig){
    if(nodo->dato == dato)
      return 1;
  }
  return 0;
}

SList slist_intersecar(SList lista1, SList lista2){
  if(slist_vacia(lista1) || slist_vacia(lista2))
    return slist_crear();
  
  SList interseccion = slist_crear();
  for(SNodo* nodo1 = lista1; nodo1 != NULL; nodo1 = nodo1->sig){
    if(slist_contiene(lista2, nodo1->dato)){
      interseccion = slist_agregar_inicio(interseccion, nodo1->dato);
    }    
  }

  return interseccion;
}

SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparadora comp){
  if(slist_vacia(lista1) || slist_vacia(lista2))
    return slist_crear();
  
  SList interseccion = slist_crear();
  for(SNodo* nodo1 = lista1; nodo1 != NULL; nodo1 = nodo1->sig){
    for(SNodo* nodo2 = lista2; nodo2 != NULL; nodo2 = nodo2->sig){
      if(comp(nodo1->dato, nodo2->dato) == 0){
        interseccion = slist_agregar_inicio(interseccion, nodo1->dato);
        break;
      }
    }
  }
  return interseccion;
}

SList slist_ordenar(SList lista, FuncionComparadora comp){
  if(slist_vacia(lista))
    return lista;
  
  SNodo nodo;
  nodo.sig = NULL;
  while(!slist_vacia(lista)){
    SNodo* head = lista;
    lista = lista->sig;
    head->sig = NULL;

    SNodo* curr = &nodo;
    while(curr->sig != NULL && comp(curr->sig->dato, head->dato) < 0){
      curr = curr->sig;
    }
    SNodo* sig = curr->sig;
    head->sig = sig;
    curr->sig = head;
  }

  return nodo.sig;
}