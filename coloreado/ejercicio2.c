#include "tablahash.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void *dato;
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
 * Ejercicio A:
 * En qué orden pueden haber sido agregado los elementos a la tabla? Suponga que sólo
 * se realizaron operaciones de inserción. Indique todas las opciones correctas.
 * 
 * Correctas: 3 y 4.
 */

/**
 * Ejercicio B:
 * Busca un dato en una tabla hash. Se asume que la tabla resuelve las colisiones utilizando
 * direccionamiento abierto y linear probing.
 */
void* tablahash_buscar_lp(TablaHash tabla, void* dato){
    if(tabla == NULL)
        return NULL;

    size_t idx = tabla->hash(dato) % tabla->capacidad;
    void* datoEncontrado = tabla->elems[idx].dato;
    if(datoEncontrado == NULL)
        return NULL;

    while(datoEncontrado != NULL){
        int comparacion = tabla->comp(datoEncontrado, dato);
        if(comparacion == 0)
            break;
        idx = (idx + 1) % tabla->capacidad;
        datoEncontrado = tabla->elems[idx].dato;
    }
    return datoEncontrado;
}

/**
 * Ejercicio C y D:
 * El problema que se presenta al borrar el elemento 3 de la tabla hash es que su posición 
 * asignada quedaría vacía y esto haría que se pierda el seguimiento a las datos que colisionaron.
 * Ejemplo:
 * Mi tabla hash es: [9, 18, NULL, 12, 3, 14, 4, 21, NULL]
 * Un posible orden de inserción de los elementos es el siguiente: 12, 14, 3, 9, 4, 18, 21.
 * Notar que con el hash propuesto, 12, 3 y 21 comparten índice en la tabla.
 * El 12 se encuentre en el índice 3, el 3 en el índice 4 y el 21 en el índice 7.
 * Al borrar el elemento 3 mi tabla quedaría así 
 * [9, 18, NULL, 12, NULL, 14, 4, 21, NULL]
 * Al utilizar linear probing para resolver colisiones, si ahora quiero buscar el elemento 21
 * los pasos serian:
 * 1er intento: indice = hash(21) % 9 = 3. Espacio ocupado y dato != 21. Fin del intento.
 * 2do intento: indice = (hash(21) + 1) % 9 = 4. Espacio vacio. Fin de la busqueda.
 * Resultado: El 21 no está en la tabla hash.
 * El resultado es erroneo, claramente.
 * Para resolver este inconveniente y que el algoritmo de busqueda propuesto siga funcionando, se deben
 * rehashear los datos de la tabla. De esta forma, si rehasheareamos encontrariamos al 21.
 * Luego de rehashear todos los elementos de la tabla, la misma quedaría de esta forma:
 * [9, 18, NULL, 12, 4, 14, 21, NULL, NULL]
 * Notar que ahora no quedarían casilleros con datos NULL entre el elemento 12 y el 21.
 * Y por lo tanto, encontrariamos el 21.
 * 
 * Otra cosa que me gustaría agregar es que la tabla del ejercicio tiene un factor de carga muy alto
 * aprox 0.77. (Recordemos que el factor de carga se define como la cantidad de elementos que tiene la tabla)
 * divido su capacidad. Una tabla con un factor de carga de 1 es una tabla llena. 
 * Al haber insertado el último elemento lo ideal hubiese sido agrandar la tabla al menos al
 * doble de su capacidad, idealmente la capacidad deberia ser el primer primo mayor al doble de la capacidad
 * actual, a fin de tener menor probabilidad de colisiones, y rehashear los elementos.
 * 
 * Si utilizamos direccionamiento abierto y no incorporamos un mecanismo de agrandamiento
 * de la tabla, al buscar un elemento podriamos caer en un bucle infinito si la tabla está llena.
 */

 // Test

static unsigned _hash(void* dato){
    unsigned n = (unsigned) *((int*) dato);
    return n;
}

static void* _copiar_entero(void* dato){
    int* n = malloc(sizeof(int));
    assert(n != NULL);
    *n = *((int*) dato);
    return n;
}

static int _comparar_entero(void* a, void* b){
    int datoA = *((int*) a);
    int datoB = *((int*) b);

    return datoA-datoB;
}

static void _destruir_entero(void* a){
    if(a == NULL)
        return;
    free(a);
}

int main(){
    TablaHash tabla = tablahash_crear(9, _copiar_entero,  _comparar_entero, _destruir_entero, _hash);
    int enteros[] = {9, 18, 0, 12, 3, 14, 4, 21, 0};
    int cant = sizeof(enteros) / sizeof(int);
    CasillaHash* arr = malloc(sizeof(CasillaHash) * sizeof(enteros) / sizeof(int));
    for(int i = 0; i < cant; i++){
        if(enteros[i] == 0){
            arr[i].dato = NULL;
            continue;
        }
        arr[i].dato = _copiar_entero(enteros + i);
    }
    free(tabla->elems);
    tabla->elems = arr;
    
    int numerosABuscarOk[] = {12, 3, 21, 9};

    for(int i = 0; i < 4; i++){
        void* datoEncontrado = tablahash_buscar_lp(tabla, numerosABuscarOk + i);
        assert(datoEncontrado != NULL); 
        int dato1 = *((int*) datoEncontrado);
        assert(dato1 == *(numerosABuscarOk + i));
    }

    int numerosQueNoEsta = 17;
    void* datoEncontrado = tablahash_buscar_lp(tabla, &numerosQueNoEsta);
    assert(datoEncontrado == NULL); 

    //Voy a agregar un numero al final de la tabla para probar el caso borde
    int* n = malloc(sizeof(int));
    *n = 8;

    CasillaHash* casilla = arr + 8;
    casilla->dato = n;

    void* datoEncontradoFinal = tablahash_buscar_lp(tabla, n);
    assert(datoEncontradoFinal != NULL); 
    int dato = *((int*) datoEncontradoFinal);
    assert(dato == *n);

    tablahash_destruir(tabla);
    puts("Tests ok");
}