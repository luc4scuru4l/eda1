#ifndef __AVL_H__
#define __AVL_H__
#include <stdio.h>

typedef void (*FuncionDestructora) (void*);
typedef int (*FuncionComparadora) (void*, void*);
typedef void* (*FuncionCopiadora) (void*);

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
 * dest
 * 
 */
void avl_destruir(AVL* arbol, FuncionDestructora destroy);

/**
 * Inserta un dato en el AVL.
 */
void avl_insertar(AVL* ptrArbol, void* dato, FuncionComparadora comp, FuncionCopiadora copiar);

#endif