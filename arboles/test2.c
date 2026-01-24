#include "bstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Casos de prueba para arboles de busqueda binaria generales
 */

#define N_PALABRAS 16
#define N_NUMEROS 10

static void *copiar_cadena(void *dato) {
  char *str = malloc(sizeof(char) * (strlen(dato) + 1));
  assert(str != NULL);
  strcpy(str, dato);
  return str;
}

static void* copiar_entero(void *dato) {
  int *n = malloc(sizeof(int));
  assert(n != NULL);
  *n = *((int*) dato);
  return n;
}

static int comparar_cadena(void *dato1, void *dato2) {
  return strcmp(dato1, dato2);
}

static int comparar_entero(void *dato1, void *dato2) {
  int a = *((int*) dato1);
  int b = *((int*) dato2);
  if (a == b)
    return 0;
  if(a > b)
    return 1;
  return -1;
}

static void destruir_cadena(void *dato) { free(dato); }

static void destruir_entero(void *dato) { free(dato); }

static void imprimir_cadena(void *dato, __attribute__((unused)) void *extra) {
  /* __attribute__((unused)) le dice al compilador que esta variable puede no
   * ser usada, de esta forma las banderas no tiran warnings.*/
  printf("\"%s\" ", (char *)dato);
}

static void imprimir_entero(void *dato, __attribute__((unused)) void *extra) {
  /* __attribute__((unused)) le dice al compilador que esta variable puede no
   * ser usada, de esta forma las banderas no tiran warnings.*/
  printf("%d ", *((int*) dato));
}
int main() {

  char *palabras[N_PALABRAS] = {"gato",      "perro",    "casa",     "persona",
                                "parque",    "arbol",    "edificio", "calle",
                                "argentina", "santa fe", "rosario",  "unr",
                                "edya",      "farmacia", "tiempo",   "celular"};
  
  int numeritos[N_NUMEROS] = {15, 9, 20, 6, 14, 17, 64, 13, 26, 72};

  // Creamos un arbol vacio y le insertamos las palabras
  BSTree arbol = bstree_crear();
  for (int i = 0; i < N_PALABRAS; i++)
    arbol = bstree_insertar(arbol, palabras[i], copiar_cadena, comparar_cadena);

  // Imprimir el arbol inorden (alfabetico)
  printf("Recorrido inorden: ");
  bstree_recorrer(arbol, BTREE_RECORRIDO_IN, imprimir_cadena, NULL);
  puts("");

  // Buscar elementos
  assert(bstree_buscar(arbol, "farmacia", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "santa fe", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "persona", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "unr", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "argentina", comparar_cadena) == 1);
  assert(bstree_buscar(arbol, "telefono", comparar_cadena) == 0);
  assert(bstree_buscar(arbol, "mail", comparar_cadena) == 0);
  assert(bstree_buscar(arbol, "parques", comparar_cadena) == 0);
  assert(bstree_buscar(arbol, "EDyA1", comparar_cadena) == 0);

  // Destruir arbol
  bstree_destruir(arbol, destruir_cadena);

  BSTree arbol_n = bstree_crear();
  for (int i = 0; i < N_NUMEROS; i++)
    arbol_n = bstree_insertar(arbol_n, &numeritos[i], copiar_entero, comparar_entero);

  printf("Recorrido inorden: ");
  bstree_recorrer(arbol_n, BTREE_RECORRIDO_IN, imprimir_entero, NULL);
  
  puts("");
  int delete = 15;
  int delete2 = 17;
  int delete3 = 20;
  int delete4 = 99;
  printf("Eliminando el %d\n", delete);
  arbol_n = bstree_eliminar(arbol_n, &delete, comparar_entero, destruir_entero);
  printf("Recorrido inorden: ");
  bstree_recorrer(arbol_n, BTREE_RECORRIDO_IN, imprimir_entero, NULL);
  puts("");

  printf("Eliminando el %d\n", delete2);
  arbol_n = bstree_eliminar(arbol_n, &delete2, comparar_entero, destruir_entero);
  printf("Recorrido inorden: ");
  bstree_recorrer(arbol_n, BTREE_RECORRIDO_IN, imprimir_entero, NULL);
  puts("");
  
  printf("Eliminando el %d\n", delete3);
  arbol_n = bstree_eliminar(arbol_n, &delete3, comparar_entero, destruir_entero);
  printf("Recorrido inorden: ");
  bstree_recorrer(arbol_n, BTREE_RECORRIDO_IN, imprimir_entero, NULL);
  puts("");

  printf("Eliminando el %d\n", delete4);
  arbol_n = bstree_eliminar(arbol_n, &delete4, comparar_entero, destruir_entero);
  printf("Recorrido inorden: ");
  bstree_recorrer(arbol_n, BTREE_RECORRIDO_IN, imprimir_entero, NULL);
  puts("");

  bstree_destruir(arbol_n, destruir_entero);
  return 0;
}
