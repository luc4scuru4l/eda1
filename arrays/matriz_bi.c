#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

struct _Matriz {
  float** direccion;
  size_t filas;
  size_t columnas;
};

Matriz matriz_crear(size_t filas, size_t columnas){
  Matriz m = malloc(sizeof(struct _Matriz));
  if(m == NULL)
    return NULL;
  
  m->direccion = malloc(sizeof(float*) * filas);
  if(m->direccion == NULL){
    free(m);
    return NULL;
  }

  float** p;
  for(p = m->direccion ; p < m->direccion + filas; p++){
    *p = malloc(sizeof(float) * columnas);
    if(*p == NULL){
      break;
    }
    for(float* i = *p; i < *p + columnas; i++)
      *i = 0;
  }

  if(p - m->direccion == (int) filas){
    m->filas = filas;
    m->columnas = columnas;
    return m;
  }

  for(float** dir = m->direccion; dir < p; dir++){
    free(*dir);
  }

  free(m->direccion);
  free(m);
  return NULL;
}


void matriz_destruir(Matriz* matriz){
  if(matriz == NULL || *matriz == NULL)
    return;
  for(float** row = (*matriz)->direccion; row < (*matriz)->direccion + (*matriz)->filas; row++){
    free(*row);
  }
  free((*matriz)->direccion);
  free(*matriz);
  *matriz = NULL;
}

float matriz_leer(Matriz matriz, size_t fila, size_t columna){
  if(matriz == NULL || fila >= matriz->filas || columna >= matriz->columnas)
    return 0;
  return *(*(matriz->direccion + fila) + columna);
}

void matriz_escribir(Matriz matriz, size_t fila, size_t columna, float dato){
  if(matriz == NULL || fila >= matriz->filas || columna >= (size_t) matriz->columnas)
    return;
  *(*(matriz->direccion + fila) + columna) = dato;
}

void matriz_intercambiar_filas(Matriz matriz, size_t fila1, size_t fila2){
  if(matriz == NULL || fila1 >= matriz->filas || fila2 >= matriz->filas)
    return;
 
  float* buffer;
  float** f1 = matriz->direccion + fila1;
  float** f2 = matriz->direccion + fila2;
  buffer = *f1;
  *f1 = *f2;
  *f2 = buffer;
}

void matriz_insertar_fila(Matriz m, size_t pos){
  if(m == NULL || pos > m->filas)
    return;
  
  float* aux = m->direccion; 
  m->direccion = realloc(m->direccion, sizeof(float*) * (m->filas + 1));
  if(m->direccion == NULL){
    m->direccion = aux;
    return;
  }

  *(m->direccion + m->filas - 1) = malloc(sizeof(float) * m->columnas);
  if(*(m->direccion + m->filas - 1) == NULL){
    
  }

  m->filas++;
  for(float** ptr = m->direccion + m->filas - 1; ptr >= m->direccion + pos + 1; ptr--)
    *ptr = *(ptr - 1);

  for(int i = 0; i < m->columnas; i++)
    *(*(m->direccion + pos) + i) = 0;
}