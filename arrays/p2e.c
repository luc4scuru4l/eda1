#include <assert.h>
#include <string.h>
#include <stdio.h>

int string_subcadena(char* str1, char* str2){
  int str1Len = strlen(str1), str2Len = strlen(str2);
  char* aux1, *aux2;
  int i;
  for(i = 0; i < str1Len - str2Len + 1; i++){
    aux1 = str1 + i;
    aux2 = str2;
    while(*aux1 == *aux2 && *aux1 != '\0'){
      aux1++;
      aux2++;
    }
    if((aux2 - str2) == str2Len){
      return i;
    } 
  }
  return -1;
}


void test_string_subcadena() {
    // Caso 1: La subcadena está al inicio
    assert(string_subcadena("algoritmos", "algo") == 0);

    // Caso 2: La subcadena está en el medio
    assert(string_subcadena("el gato pardo", "gato") == 3);

    // Caso 3: La subcadena está al final
    assert(string_subcadena("unr rosario", "rio") == 8);

    // Caso 4: La subcadena no existe en str1
    assert(string_subcadena("estructuras", "datos") == -1);

    // Caso 5: Ambas cadenas son idénticas
    assert(string_subcadena("prueba", "prueba") == 0);

    // Caso 6: str2 es más larga que str1
    assert(string_subcadena("abc", "abcdef") == -1);

    // Caso 7: str2 ocurre varias veces (debe retornar la primera)
    // "banana" -> "ana" empieza en el índice 1 y en el 3.
    assert(string_subcadena("banana", "ana") == 1);

    // Caso 8: Diferencia por mayúsculas
    assert(string_subcadena("Rosario", "rosario") == -1);

    // Caso 9: Subcadena de un solo carácter
    assert(string_subcadena("lenguaje c", "c") == 9);

    // Caso 10: str1 es vacía
    assert(string_subcadena("", "algo") == -1);

    puts("Yay!");
}

int main(){
  test_string_subcadena(); 
  return 0;
}