#ifndef __AVL_H__
#define __AVL_H__
#include <stdio.h>

typedef void (*FuncionDestructora) (void*);
typedef int (*FuncionComparadora) (void*, void*);
typedef void* (*FuncionCopiadora) (void*);
typedef void (*FuncionVisitanteExtra) (void*, void*);

typedef struct _AVL {
  void* dato;
  size_t altura;
  AVL izq;
  AVL der;
} *AVL;

/**
 * Crea un AVL vacío.
 */
AVL avl_crear();

/**
 * Destruye un AVL.
 */
void avl_destruir(AVL* arbol, FuncionDestructora destroy);

/**
 * Recorre un AVL.
 */

void avl_recorrer(AVL arbol, void* extra, FuncionVisitanteExtra visit);

/**
 * Inserta un dato en el AVL.
 */
void avl_insertar(AVL* ptrArbol, void* dato, FuncionComparadora comp, FuncionCopiadora copiar);

/**
 * Elimina un dato del AVL.
 */
void avl_eliminar(AVL* ptrArbol, void* dato, FuncionComparadora comp, FuncionDestructora destroy);

#endif