#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matriz.h"

void test_matriz(){
  Matriz m = matriz_crear(2, 2);
  matriz_escribir(m, 0, 0, 4);
  matriz_escribir(m, 0, 1, 1);
  matriz_escribir(m, 1, 0, 7);
  matriz_escribir(m, 1, 1, 10);

  assert(matriz_leer(m, 0, 0) == 4);
  assert(matriz_leer(m, 0, 1) == 1);
  assert(matriz_leer(m, 1, 0) == 7);
  assert(matriz_leer(m, 1, 1) == 10);
  
  matriz_intercambiar_filas(m, 0, 1);
  assert(matriz_leer(m, 0, 0) == 7);
  assert(matriz_leer(m, 0, 1) == 10);

  matriz_destruir(&m);
  assert(m == NULL);

  
  puts("Yay!!!");
}

int main(){
  test_matriz();
  return 0;
}