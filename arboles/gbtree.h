#include "../ghelpers.h"
#ifndef __GBTREE_H__
#define __GBTREE_H__

typedef struct _GBTree {
  void* dato;
  struct _GBTree* left;
  struct _GBTree* right;
}* GBTree;

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

/**
 * Crea un arbol binario.
 */
GBTree gbtree_crear();

/**
 * Destruye un arbol
 */
void gbtree_destruir(GBTree, FuncionDestructora);

/**
 * Retorna 1 si un árbol está vacío. 0 en caso contrario.
 */
int gbtree_empty(GBTree);

/**
 * Crea un nuevo árbol, con el dato dado en el nodo raíz, y los
 * subarboles datos a izquierda y derecha.
 */
GBTree gbtree_unir(void*, GBTree, GBTree);

/**
 * Crea un nuevo árbol, con el dato entero dado en el nodo raíz, y los
 * subarboles datos a izquierda y derecha.
 */
GBTree gbtree_unir_entero(int, GBTree, GBTree);

/**
 * Recorre un arbol;
 */
void gbtree_recorrer(GBTree, BTreeOrdenDeRecorrido, FuncionVisitante);

/**
 * Retorna la cantidad de nodos del arbol;
 */
int gbtree_nnodos(GBTree);

/**
 * Retorna 1 si el dato buscado se encuentra en el arbol. 
 * De lo contrario retorna 0
 */
int gbtree_buscar(GBTree, void*, FuncionComparadora);

/**
 * Retorna una copia del arbol dado. 
 */
GBTree gbtree_copiar(GBTree, FuncionCopiadora);

/**
 * Retorna 1 si el arbol es una hoja. 0 en caso contrario. 
 */
int gbtree_es_hoja(GBTree);

/**
 * Retorna la altura del arbol
 */
int gbtree_altura(GBTree);

/**
 * Retorna la cantidad de nodos en la profundidad dada
 */
int gbtree_nnodos_profundidad(GBTree, int);

/**
 * Retorna la profundida del nodo que contiene el dato dado, y -1 si el número no se encuentra en el árbol. 
 * La búsqueda será PREORDER, se retorna la primera altura encontrada.
 */
int gbtree_profundidad(GBTree, void*, FuncionComparadora);

/**
 * Recorre un arbol utilizando el algoritmo BFS. 
 */
void gbtree_recorrer_bfs_i(GBTree arbol, FuncionVisitante visit);

#endif