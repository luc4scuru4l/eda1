#include "cola_prioridad.h"
#include <assert.h>

int cola_prioridad_es_vacia(ColaPrioridad cola){
  return bheap_es_vacio(cola);
}

void* cola_prioridad_maximo(ColaPrioridad cola){
  if(cola_prioridad_es_vacia(cola))
    return NULL;
  return *(cola->arr + 1);
}

void cola_prioridad_eliminar_maximo(ColaPrioridad* cola, FuncionDestructora destr){
  if(cola_prioridad_es_vacia(cola))
    return;
  ColaPrioridad aux = *cola;
  bheap_eliminar(cola, *(aux->arr + 1), destr);
}

void cola_prioridad_insertar(ColaPrioridad* cola, void* dato, FuncionCopiadora copy){
  bheap_insertar(cola, dato, copy);
}