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
    if(destr != NULL)
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

// GList glist_invertir(GList lista){
//   if(lista == NULL || lista->sig == NULL)
//     return lista;
  
//   Pila pila = pila_crear();
//   for(GNodo* nodo = lista; nodo != NULL; nodo = nodo->sig){
//     pila = pila_apilar(pila, nodo);
//   }
//   GNodo* first = (GNodo *) pila_tope(pila);
//   pila = pila_desapilar(pila, NULL);
//   GNodo* current = first;

//   while(!pila_es_vacia(pila)){
//     current->sig = (GNodo *) pila_tope(pila);
//     pila = pila_desapilar(pila, NULL);
//     current = current->sig;
//   }

//   current->sig = NULL;

//   return first;
// }

void* glist_obtener_primero(GList lista){
  if(NULL == lista)
    return NULL;
  return lista->dato;
}

void glist_eliminar_primero(GList* lista, FuncionDestructora destr){
  if(NULL == lista || NULL == *lista)
    return;
  GNodo* primero = *lista;
  *lista = (*lista)->sig;
  primero->sig = NULL;

  glist_destruir(&primero, destr);
}

void* glist_encontrar(GList lista, void* dato, FuncionComparadora comp){
  if(lista == NULL)
    return NULL;
  for(GNodo* nodo = lista; nodo != NULL; nodo = nodo->sig){
    if(comp(nodo->dato, dato) == 0)
      return nodo->dato;
  }
  return NULL;
}

int glist_eliminar(GList* ptrLista, void* dato, FuncionComparadora comp, FuncionDestructora destr){
  if(ptrLista == NULL || *ptrLista == NULL)
    return 0;
  GList lista = *ptrLista;
  GNodo* anterior = NULL;
  GNodo* nodo;
  for(nodo = lista; nodo != NULL; nodo = nodo->sig){
    if(comp(nodo->dato, dato) == 0)
      break;
    anterior = nodo;
  }
  // Si el dato a eliminar es el primero
  if(anterior == NULL){
    *ptrLista = nodo->sig;
    destr(nodo->dato);
    free(nodo);
    return 1;
  }
  // No se encontró el nodo a eliminar
  if(nodo == NULL) 
    return 0;
  
  anterior->sig = nodo->sig;
  destr(nodo->dato);
  free(nodo);
  return 1;
}

int glist_reemplazar(GList* ptrLista, void* dato, void* nuevoDato, FuncionComparadora comp, FuncionDestructora destr){
  if(ptrLista == NULL || *ptrLista == NULL)
    return 0;
  GList lista = *ptrLista;
  GNodo* anterior = NULL;
  GNodo* nodo;
  for(nodo = lista; nodo != NULL; nodo = nodo->sig){
    if(comp(nodo->dato, dato) == 0)
      break;
    anterior = nodo;
  }
  // Si el dato a reemplazar es el primero
  if(anterior == NULL){
    *ptrLista = glist_agregar_inicio(nodo->sig, nuevoDato);
    destr(nodo->dato);
    free(nodo);
    return 1;
  }
  // No se encontró el nodo a eliminar
  if(nodo == NULL) 
    return 0;
  
  anterior->sig = glist_agregar_inicio(nodo->sig, nuevoDato);
  destr(nodo->dato);
  free(nodo);
  return 1;
}

void glist_recorrer_extra(GList lista, void* extra, FuncionVisitanteExtra visit){
  for(GNodo* nodo = lista; nodo != NULL; nodo = nodo->sig){
    visit(nodo->dato, extra);
  }
}