#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int* direccion;
  int capacidad;
} ArregloEnteros;

ArregloEnteros* arreglo_enteros_crear(int capacidad){
  if(capacidad < 1)
    return NULL;

  ArregloEnteros* arr = malloc(sizeof(ArregloEnteros));
  if(arr == NULL)
    return NULL;
  
  arr->direccion = malloc(sizeof(int) * capacidad);
  if(arr->direccion == NULL){
    free(arr);
    return NULL;
  }
  for(int i = 0; i < capacidad; i++){
    arr->direccion[i] = 0;
  }
  arr->capacidad = capacidad;
  return arr;
}

void arreglo_enteros_destruir(ArregloEnteros* arreglo){
  if(arreglo == NULL)
    return;

  free(arreglo->direccion);
  free(arreglo);
}

int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos){
  if(arreglo == NULL || pos < 0 || pos >= arreglo->capacidad)
    exit(1);
  return arreglo->direccion[pos];
}

void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato){
  if(arreglo == NULL || pos < 0 || pos >= arreglo->capacidad)
    exit(1);
  arreglo->direccion[pos] = dato;
}

int arreglo_enteros_capacidad(ArregloEnteros* arreglo){
  if(arreglo == NULL)
    exit(1);
  return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros* arreglo){
  if(arreglo == NULL)
    exit(1);
  for(int i = 0; i < arreglo->capacidad; i++){
    printf("%d ", arreglo->direccion[i]);
  }
  printf("\n");
}

void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int capacidad){
  if(arreglo == NULL || capacidad < 1)
    exit(1);
  arreglo->direccion = realloc(arreglo->direccion, sizeof(int) * capacidad);
  if(arreglo->direccion == NULL){
    exit(1);
  }
  arreglo->capacidad = capacidad;
}

void arreglo_enteros_insertar(ArregloEnteros* arreglo, int pos, int dato){
  if(arreglo == NULL || pos < 0 || pos >= arreglo->capacidad + 1)
    exit(1);
  arreglo_enteros_ajustar(arreglo, arreglo->capacidad + 1);
  for(int i = arreglo->capacidad - 2; i >= pos; i--)
    *(arreglo->direccion + i + 1) = *(arreglo->direccion + i);
  *(arreglo->direccion + pos) = dato;  
}

void arreglo_enteros_eliminar(ArregloEnteros* arreglo, int pos){
  if(arreglo == NULL || pos < 0 || pos >= arreglo->capacidad || arreglo->capacidad == 1)
    exit(1);
  for(int i = pos; i < arreglo->capacidad - 1; i++)
    *(arreglo->direccion + i) = *(arreglo->direccion + i + 1);
  arreglo_enteros_ajustar(arreglo, arreglo->capacidad - 1);
}

void test_arreglo_enteros() {
    int cap = 5;
    ArregloEnteros* arr = arreglo_enteros_crear(cap);

    // 1. Test de Creación
    assert(arr != NULL); // La estructura debe existir
    assert(arr->direccion != NULL); // El buffer interno debe estar reservado
    assert(arreglo_enteros_capacidad(arr) == cap);

    // 2. Test de Escritura y Lectura (Caso típico)
    arreglo_enteros_escribir(arr, 0, 100);
    arreglo_enteros_escribir(arr, 2, 200);
    arreglo_enteros_escribir(arr, 4, 400);

    assert(arreglo_enteros_leer(arr, 0) == 100);
    assert(arreglo_enteros_leer(arr, 2) == 200);
    assert(arreglo_enteros_leer(arr, 4) == 400);

    // 3. Test de Persistencia (Que una escritura no rompa otra)
    arreglo_enteros_escribir(arr, 0, 50);
    assert(arreglo_enteros_leer(arr, 0) == 50);
    assert(arreglo_enteros_leer(arr, 2) == 200); // Sigue siendo 200

    // 4. Test de límites (Opcional, si tu función maneja errores)
    // Si tus funciones retornan algo específico en error, testealo acá.

    // 5. Destrucción
    arreglo_enteros_destruir(arr);
    // Nota: Después de destruir, no podés usar asserts sobre 'arr' 
    // porque esa memoria ya no es tuya.

    puts("Yay!!");
}

void test_arreglo_dinamico() {
    // Usamos una capacidad inicial de 3
    ArregloEnteros* arr = arreglo_enteros_crear(3);
    arreglo_enteros_escribir(arr, 0, 10);
    arreglo_enteros_escribir(arr, 1, 20);
    arreglo_enteros_escribir(arr, 2, 30);

    // --- TEST A: Ajustar (Agrandar y Achicar) ---
    arreglo_enteros_ajustar(arr, 5);
    assert(arreglo_enteros_capacidad(arr) == 5);
    assert(arreglo_enteros_leer(arr, 0) == 10); // Los datos se mantienen
    
    arreglo_enteros_ajustar(arr, 2); 
    assert(arreglo_enteros_capacidad(arr) == 2);
    assert(arreglo_enteros_leer(arr, 1) == 20);
    // (El 30 se perdió por el truncado)

    // --- TEST B: Insertar ---
    // Estado actual: [10, 20], Capacidad: 2
    // Insertamos un 15 en la posición 1 -> Resultado esperado: [10, 15, 20]
    arreglo_enteros_insertar(arr, 1, 15);
    assert(arreglo_enteros_capacidad(arr) == 3);
    assert(arreglo_enteros_leer(arr, 0) == 10);
    assert(arreglo_enteros_leer(arr, 1) == 15);
    assert(arreglo_enteros_leer(arr, 2) == 20);

    // Insertar al inicio
    arreglo_enteros_insertar(arr, 0, 5); // [5, 10, 15, 20]
    assert(arreglo_enteros_leer(arr, 0) == 5);
    assert(arreglo_enteros_leer(arr, 1) == 10);

    // --- TEST C: Eliminar ---
    // Estado actual: [5, 10, 15, 20], Capacidad: 4
    // Eliminamos la posición 1 (el 10) -> Resultado: [5, 15, 20]
    arreglo_enteros_eliminar(arr, 1);
    assert(arreglo_enteros_capacidad(arr) == 3);
    assert(arreglo_enteros_leer(arr, 0) == 5);
    assert(arreglo_enteros_leer(arr, 1) == 15);
    assert(arreglo_enteros_leer(arr, 2) == 20);

    // Eliminar el último
    arreglo_enteros_eliminar(arr, 2); // [5, 15]
    assert(arreglo_enteros_capacidad(arr) == 2);
    
    arreglo_enteros_destruir(arr);

    puts("Yay!x2");
}

int main(){
  test_arreglo_enteros(); 
  test_arreglo_dinamico();
  return 0;
}