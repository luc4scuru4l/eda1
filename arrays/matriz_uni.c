#include "matriz.h"
#include <stdlib.h>

struct _Matriz {
  float* direccion;
  size_t filas;
  size_t columnas;
};

Matriz matriz_crear(size_t filas, size_t columnas){
  Matriz m = malloc(sizeof(struct _Matriz));
  if(m == NULL)
    return m;
  
  m->direccion = malloc(sizeof(float) * filas * columnas);
  if(m->direccion == NULL){
    free(m);
    return NULL;
  }

  for(float* ptr = m->direccion; ptr < m->direccion + filas * columnas; ptr++){
    *ptr = 0;
  }

  m->filas = filas;
  m->columnas = columnas;

  return m;
}

void matriz_destruir(Matriz* matriz){
  if(matriz == NULL || *matriz == NULL)
    return;
  free((*matriz)->direccion);
  free(*matriz);
  *matriz = NULL;
}

float matriz_leer(Matriz matriz, size_t fila, size_t columna){
  if(matriz == NULL || fila >= matriz->filas || columna >= matriz->columnas)
    return 0;
  return *(matriz->direccion + (matriz->columnas * fila + columna));
}

void matriz_escribir(Matriz matriz, size_t fila, size_t columna, float dato){
  if(matriz == NULL || fila >= matriz->filas || columna >= matriz->columnas)
    return;
  *(matriz->direccion + (matriz->columnas * fila + columna)) = dato;
}

void matriz_intercambiar_filas(Matriz matriz, size_t fila1, size_t fila2){
  if(matriz == NULL || fila1 >= matriz->filas || fila2 >= matriz->filas)
    return;
  float *f1 = matriz->direccion + fila1 * matriz->columnas;
  float *f2 = matriz->direccion + fila2 * matriz->columnas;
  for(size_t i = 0; i < matriz->columnas; i ++){
    float aux = *(f1 + i);
    *(f1 + i) = *(f2 + i);
    *(f2 + i) = aux;
  }
}

void matriz_insertar_fila(Matriz m, size_t pos){
  if(m == NULL || pos > m->filas)
    return;
  
  float* aux = m->direccion; 
  m->direccion = realloc(m->direccion, sizeof(float) * (m->filas + 1) * m->columnas);
  if(m->direccion == NULL){
    m->direccion = aux;
    return;
  }
  
  m->filas++;
  for(float* ptr = m->direccion + (m->filas * m->columnas) - 1; ptr >= m->direccion + pos * m->columnas + m->columnas; ptr--)
    *ptr = *(ptr - m->columnas);

  for(int i = 0; i < m->columnas; i++)
    *(m->direccion + pos * m->columnas + i) = 0;
}