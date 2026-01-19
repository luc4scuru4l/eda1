#include "gcola.h"
#include <stdlib.h>

GCola gcola_crear(){
  return glist_crear();
}

int gcola_es_vacia(GCola cola){
  return NULL == cola;
}

void* gcola_inicio(GCola cola){
  return glist_obtener_primero(cola);
}

void gcola_desencolar(GCola* cola, FuncionDestructora destr){
  glist_eliminar_primero(cola, destr);
}

void gcola_destruir(GCola* cola, FuncionDestructora destr){
  glist_destruir(cola, destr);
}

GCola gcola_encolar(GCola cola, void* dato){
  return glist_agregar_final(cola, dato);
}