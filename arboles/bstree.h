#include "../ghelpers.h"
#include "../arboles/gbtree.h"
#ifndef __BSTREE_H__
#define __BSTREE_H__

typedef GBTree BSTree;

/**
 * Retorna un arbol de busqueda binaria vacio.
 */
BSTree bstree_crear();

/**
 * Destruye el arbol y sus datos.
 */
void bstree_destruir(BSTree, FuncionDestructora);

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario.
 */
int bstree_buscar(BSTree, void *, FuncionComparadora);

/**
 * Inserta un dato no repetido en el arbol, manteniendo la propiedad del arbol
 * de busqueda binaria.
 */
BSTree bstree_insertar(BSTree, void *, FuncionCopiadora, FuncionComparadora);

/**
 * Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree, BTreeOrdenDeRecorrido, FuncionVisitanteExtra,
                     void *extra);

/**
 * Elimina un nodo de un ABB.
 */
BSTree bstree_eliminar(BSTree arbol, void *dato, FuncionComparadora, FuncionDestructora);

#endif //__BSTREE_H__