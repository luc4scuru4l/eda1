#ifndef __GLIST_H__
#define __GLIST_H__

typedef struct _GNodo {
  void* dato;
  struct _GNodo* sig;
} GNodo;

typedef GNodo* GList;
typedef void (*FuncionDestructora)(void* dato);
typedef void (*FuncionVisitante)(void* dato);

/**
 * Crea una lista general vacía
 * 
 */
GList glist_crear();

/**
 * Limpia de la memoria una lista general. 
 */
void glist_destruir(GList* lista, FuncionDestructora destr);

/**
 * Agrega un dato al inicio de la lista
 */
GList glist_agregar_inicio(GList lista, void* dato);

/**
 * Agrega un dato al final de una lista
 */
GList glist_agregar_final(GList lista, void* dato);

/**
 * Recorre una lista aplicando la funcion visitante a cada nodos
 */
void glist_recorrer(GList lista, FuncionVisitante visit);

/**
 * Invierte los elementos de una lista
 */
GList glist_invertir(GList lista);

/**
 * Retorna el dato del primer elemento de la lista. Sin eliminarlo.
 */
void* glist_obtener_primero(GList lista);

/**
 * Elimina el primer nodo de la lista.
 */
void glist_eliminar_primero(GList* lista, FuncionDestructora destr);
#endif