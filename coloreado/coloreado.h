#ifndef __COLOREADO_H__
#define __COLOREADO_H__
 
typedef enum color { Rojo , Azul , Neutro } Color;
typedef struct Nodo_ {
    char * cdato ;
    Color colorNodo ;
    struct Nodo_ * der , * izq ;
} Nodo ;

typedef Nodo* ArbolBinarioColoreado ;

// Crea un arbol coloreado vacío.
ArbolBinarioColoreado coloreado_crear();

/**
 * Crea un nuevo arbol, con el color dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
ArbolBinarioColoreado coloreado_unir(Color color, ArbolBinarioColoreado left, ArbolBinarioColoreado right);

// Retorna el color del Arbol .
Color color ( ArbolBinarioColoreado inicio );

// Retorna la cantidad de hojas puras.
int CantidadPuras ( ArbolBinarioColoreado inicio );

// Destruye un arbol coloreado.
void coloreado_destruir(ArbolBinarioColoreado* ptrArbol);
#endif