#include "coloreado.h"
#include <stdlib.h>
#include <assert.h>

typedef struct _Contador{
    size_t azul;
    size_t rojo;
    size_t neutro;
} Contador;


static void _coloreado_llenar_contador(ArbolBinarioColoreado arbol, Contador* contador){
    if(arbol == NULL)
        return;
    if(arbol->colorNodo == Azul){
        contador->azul++;
    }else if(arbol->colorNodo == Rojo){
        contador->rojo++;
    }else{
        contador->neutro++;
    }
    _coloreado_llenar_contador(arbol->izq, contador);
    _coloreado_llenar_contador(arbol->der, contador);
}

Color color (ArbolBinarioColoreado inicio){
    Contador contador;
    contador.azul = 0;
    contador.rojo = 0;
    contador.neutro = 0;
    _coloreado_llenar_contador(inicio, &contador);
    if(contador.rojo == contador.azul)
        return Neutro;
    if(contador.rojo > contador.azul)
        return Rojo;
    return Azul;
}

static int _coloreado_cantidad_puras(ArbolBinarioColoreado arbol, Color colorPadre){
    if(arbol == NULL)
        return 0;
    if(arbol->colorNodo != colorPadre)
        return 0;
    if(arbol->izq == NULL && arbol->der == NULL){ // Es una hoja
        return 1;
    }
    return _coloreado_cantidad_puras(arbol->izq, arbol->colorNodo) + 
           _coloreado_cantidad_puras(arbol->der, arbol->colorNodo);
}

int CantidadPuras (ArbolBinarioColoreado inicio){
    assert(inicio != NULL);
    return _coloreado_cantidad_puras(inicio->izq, inicio->colorNodo) +
           _coloreado_cantidad_puras(inicio->der, inicio->colorNodo);
}

ArbolBinarioColoreado coloreado_unir(Color color, ArbolBinarioColoreado left, ArbolBinarioColoreado right) {
  ArbolBinarioColoreado nuevoNodo = malloc(sizeof(struct Nodo_));
  assert(nuevoNodo != NULL);
  nuevoNodo->colorNodo = color;
  nuevoNodo->cdato = NULL;
  nuevoNodo->izq = left;
  nuevoNodo->der = right;
  return nuevoNodo;
}

ArbolBinarioColoreado coloreado_crear(){
    return NULL;
}

void coloreado_destruir(ArbolBinarioColoreado* ptrArbol){
    assert(ptrArbol != NULL);
    if(*ptrArbol == NULL)
        return;
    ArbolBinarioColoreado arbol = *ptrArbol;
    coloreado_destruir(&(arbol->izq));
    coloreado_destruir(&(arbol->der));
    free(*ptrArbol);
    *ptrArbol = NULL;
}