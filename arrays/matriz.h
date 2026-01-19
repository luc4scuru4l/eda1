#ifndef __MATRIZ_H__
#define __MATRIZ_H__
#include <stdlib.h>
typedef struct _Matriz *Matriz;

Matriz matriz_crear(size_t filas, size_t columnas);

void matriz_destruir(Matriz* matriz);

float matriz_leer(Matriz matriz, size_t fila, size_t columna);

void matriz_escribir(Matriz matriz, size_t fila, size_t columna, float dato);

void matriz_intercambiar_filas(Matriz matriz, size_t fila1, size_t fila2);

#endif