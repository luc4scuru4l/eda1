#include "../listas/glist.h"
#ifndef __G_COLA_H__
#define __G_COLA_H__

typedef GList GCola;

/**
 * Crea una cola vacía.
 */
GCola gcola_crear();

/**
 * Retorna 1 si la cola está vacía o 0 en caso contrario
 */
int gcola_es_vacia(GCola cola);

/**
 * Retorna el primer elemento de la cola sin eliminarlo.
 */
void* gcola_inicio(GCola cola);

/**
 * Elimina el primer elemento de la cola.
 */
void gcola_desencolar(GCola* cola, FuncionDestructora destr);

/**
 * Añade un elemento al final de la cola.
 */
GCola gcola_encolar(GCola cola, void* dato);

/**
 * Destruye una cola. 
 */
void gcola_destruir(GCola* cola, FuncionDestructora destr);
#endif