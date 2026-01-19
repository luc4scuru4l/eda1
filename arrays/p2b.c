#include <assert.h>
#include <string.h>
#include <stdio.h>


void string_reverse(char* str){
  int length = strlen(str);
  for(int i = 0; i < length / 2; i++){
    int idx = length - 1 - i;
    char aux = *(str + idx);
    *(str + idx) = *(str + i);
    *(str + i) = aux;
  }
}

void test_string_reverse() {
    // Caso 1: Cadena vacía
    char test1[] = "";
    string_reverse(test1);
    assert(strcmp(test1, "") == 0);

    // Caso 2: Un solo carácter
    char test2[] = "X";
    string_reverse(test2);
    assert(strcmp(test2, "X") == 0);

    // Caso 3: Longitud par
    char test3[] = "C-sharp";
    string_reverse(test3);
    assert(strcmp(test3, "prahs-C") == 0);

    // Caso 4: Longitud impar
    char test4[] = "Rosario";
    string_reverse(test4);
    assert(strcmp(test4, "oirasoR") == 0);

    // Caso 5: Palíndromo
    char test5[] = "neuquen";
    string_reverse(test5);
    assert(strcmp(test5, "neuquen") == 0);

    // Caso 6: Cadena con espacios
    char test6[] = "hola mundo";
    string_reverse(test6);
    assert(strcmp(test6, "odnum aloh") == 0);

    printf("Yay! todos los test pasaron\n");
}

int main(){
  test_string_reverse();
  return 0;
}