#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitante) (int dato);
typedef int (*FuncionComparadora) (int, int);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

/**
 * Retorna la longitud de una lista.
 */
size_t slist_longitud(SList lista);

/**
 * Concatena dos listas, modificando la primera
 */
void slist_concatenar(SList l1, SList l2);

/**
 * Inserta un elemento en una posición arbitraria
 */
SList slist_insertar(SList lista, size_t pos, int dato);

/**
 * Elimina un nodo en una posición arbitraria
 */
SList slist_eliminar(SList lista, size_t pos);

/**
 * Retorna 1 si un dato está en la lista. 0 en caso contrario.
 */
int slist_contiene(SList lista, int dato);

/**
 * Retorna una lista con la interseccion de las dos listas pasadas como argumento
 */
SList slist_intersecar(SList lista1, SList lista2);

/**
 * Retorna una lista con la interseccion de las dos listas pasadas como argumento, utilizando la
 * comparación de la función comparadora
 */
SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparadora comp);

/**
 * Ordena una lista 
 */
SList slist_ordenar(SList lista, FuncionComparadora comp);

#endif /* __SLIST_H__ */

