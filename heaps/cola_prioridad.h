#ifndef __COLAP_H__
#define __COLAP_H__

#include "bheap.h"

typedef BHeap ColaPrioridad;

/**
 * Retorna 1 si la cola de prioridad está vacía. 0 en caso contrario.
 */
int cola_prioridad_es_vacia(ColaPrioridad);

/**
 * Retorna el elemento de mayor prioridad de la cola, sin eliminarlo;
 */
void* cola_prioridad_maximo(ColaPrioridad);

/**
 * Eliminar el elemento de mayor prioridad de la cola.
 */
void cola_prioridad_eliminar_maximo(ColaPrioridad, FuncionDestructora);

/**
 * Inserta un elemento en la cola.
 */
void cola_prioridad_insertar(ColaPrioridad* cola, void* dato, FuncionCopiadora copy);

#endif
