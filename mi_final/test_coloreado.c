#include "coloreado.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    ArbolBinarioColoreado hoja1 = coloreado_unir(Azul, NULL, NULL);
    ArbolBinarioColoreado hoja2 = coloreado_unir(Rojo, NULL, NULL);
    ArbolBinarioColoreado hijo_i = coloreado_unir(Azul, hoja1, hoja2);

    ArbolBinarioColoreado hoja3 = coloreado_unir(Rojo, NULL, NULL);
    
    ArbolBinarioColoreado raiz = coloreado_unir(Azul, hijo_i, hoja3);

    assert(color(raiz) == Azul);
    assert(CantidadPuras(raiz) == 1);

    hoja2->colorNodo = Azul;
    // Ahora deberian haber dos hojas puras
    assert(CantidadPuras(raiz) == 2);

    //Lo vuelvo a dejar como antes
    hoja2->colorNodo = Rojo;
    
    ArbolBinarioColoreado hojaRoja1 = coloreado_unir(Rojo, NULL, NULL);
    ArbolBinarioColoreado hojaRoja2 = coloreado_unir(Rojo, NULL, NULL);
    hoja3->izq = hojaRoja1;
    hoja3->der = hojaRoja2;

    //Ahora el arbol debería ser rojo
    assert(color(raiz) == Rojo);

    ArbolBinarioColoreado hojaAzul1 = coloreado_unir(Azul, NULL, NULL);
    hojaRoja2->der= hojaAzul1;
    //Ahora el arbol debería ser neutro
    assert(color(raiz) == Neutro);

    coloreado_destruir(&raiz);
    puts("Tests ok");
}