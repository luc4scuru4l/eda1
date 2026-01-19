#include "../listas/glist.h"
#ifndef __GSTACK_H__
#define __GSTACK_H__

typedef GList Pila;

/**
 * Crea una pila vacía
 */
Pila pila_crear();

/**
 * Libera la memoria utilizada por una pila
 */
void pila_destruir(Pila* pila, FuncionDestructora destr);

/**
 * Retorna 1 si la pila está vacía. 0 en caso contrario. 
 */
int pila_es_vacia(Pila pila);

/**
 * Retorna el elemento tope de la pila, pero sin eliminarlo. 
 */
void* pila_tope(Pila pila);

/**
 * Apila un elemento en la pila. 
 */
Pila pila_apilar(Pila pila, void* dato);

/**
 * Elimina el elemento tope de la pila.
 */
Pila pila_desapilar(Pila pila, FuncionDestructora destr);

#endif