/**
 * IMPLEMENTACIÓN TABLAS HASH UTILIZANDO ENCADENAMIENTO Y ÁREA DE REBALSE
 */
#include "tablahash.h"
#include "../listas/glist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  GList rebalse;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].rebalse = NULL;
  }

  return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx)
    if (tabla->elems[idx].rebalse != NULL){
        glist_destruir(&(tabla->elems[idx].rebalse), tabla->destr);
    }

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 * IMPORTANTE: La implementacion no maneja colisiones.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  void* nodo = glist_encontrar(tabla->elems[idx].rebalse, dato, tabla->comp);
  if(nodo == NULL){
    tabla->elems[idx].rebalse = glist_agregar_inicio(tabla->elems[idx].rebalse, tabla->copia(dato));
    tabla->numElems++;
    return;
  }
  
  glist_reemplazar(&(tabla->elems[idx].rebalse), nodo, tabla->copia(dato), tabla->comp, tabla->destr);
}

// typedef struct {
//   char *nombre;
//   char *tel;
//   unsigned int edad;
// } Test;

// static void imprimir(void* contacto){
//   Test c = *((Test*) contacto);
//   printf("{%s, %s, %d}", c.nombre, c.tel, c.edad);
// }
/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void* tablahash_buscar(TablaHash tabla, void *dato) {
  assert(tabla != NULL);
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // printf("ESTOY POR BUSCAR A: ");
  // imprimir(dato);
  // puts("");

  // Retornar NULL si la casilla estaba vacia.
  if (tabla->elems[idx].rebalse == NULL)
    return NULL;
  void* datoBuscado = glist_encontrar(tabla->elems[idx].rebalse, dato, tabla->comp);
  if (datoBuscado != NULL)
    return datoBuscado;
  // Retornar NULL en otro caso.
  return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar si la casilla estaba vacia.
  if (tabla->elems[idx].rebalse == NULL)
    return;

  int resultado = glist_eliminar(&(tabla->elems[idx].rebalse), dato, tabla->comp, tabla->destr);
  if(resultado == 1)
    tabla->numElems--;
}