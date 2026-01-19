#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

static int comparar1(int a, int b){
  return (a < b) ? -1 : (a > b) ? 1 : 0;
}

static int comparar2(int a, int b){
  return (a < b) ? 1 : (a > b) ? -1 : 0;
}

int main() {

  SList lista = slist_crear();
  lista = slist_agregar_inicio(lista, 5);
  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 1);
  lista = slist_agregar_final(lista, 7);

  SList lista2 = slist_crear();
  lista2 = slist_agregar_inicio(lista2, 6);
  lista2 = slist_agregar_inicio(lista2, 4);
  lista2 = slist_agregar_inicio(lista2, 2);
  lista2 = slist_agregar_final(lista2, 8);

  slist_recorrer(lista, imprimir_entero);
  puts("");

  slist_recorrer(lista2, imprimir_entero);
  puts("");

  printf("La longitud de la primera lista es %ld\n", slist_longitud(lista));
  printf("La longitud de la segunda lista es %ld\n", slist_longitud(lista2));
  
  slist_concatenar(lista, lista2);

  puts("La concatenación es:");
  slist_recorrer(lista, imprimir_entero);
  puts("");

  puts("Insetando un 0 al inicio, al final y entre el 7 y el 2");
  lista = slist_insertar(lista, 4, 0);
  lista = slist_insertar(lista, 0, 0);
  lista = slist_insertar(lista, slist_longitud(lista), 0);

  slist_recorrer(lista, imprimir_entero);
  puts("");
  puts("Ahora borro los 0's que agregué:");
  lista = slist_eliminar(lista, 5);
  lista = slist_eliminar(lista, 0);
  lista = slist_eliminar(lista, slist_longitud(lista));
  slist_recorrer(lista, imprimir_entero);
  puts("");

  printf("El dato 2, está en la lista? %s\n", (slist_contiene(lista, 2) == 1) ? "Sí" : "No");
  printf("El dato 20, está en la lista? %s\n", (slist_contiene(lista, 20) == 1) ? "Sí" : "No");

  puts("Ahora voy a ordenar la lista:");
  lista = slist_ordenar(lista, comparar1);
  slist_recorrer(lista, imprimir_entero); 
  puts("");

  puts("Ahora voy a ordenar la lista al reves:");
  lista = slist_ordenar(lista, comparar2);
  slist_recorrer(lista, imprimir_entero); 
  puts("");


  slist_destruir(lista);
  slist_destruir(lista2);

  return 0;
}
