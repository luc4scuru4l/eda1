#include<stdio.h>
#include<assert.h>

int string_len(char* str){
  int idx = 0;
  while(*(str++) != '\0')
    idx++;
  return idx;
}

void test_string_len() {
    // Caso 1: Cadena vacía (Solo contiene el \0)
    assert(string_len("") == 0);

    // Caso 2: Un solo carácter
    assert(string_len("F") == 1);

    // Caso 3: Cadena común
    assert(string_len("Hola") == 4);

    // Caso 4: Cadena con espacios (El espacio cuenta como carácter)
    assert(string_len("UNR Rosario") == 11);

    // Caso 5: Cadena con caracteres de escape
    // \n es UN solo carácter (salto de línea)
    assert(string_len("C\n") == 2); 

    // Caso 6: Cadena larga
    assert(string_len("Desarrollo de Software") == 22);
    
    printf("Todos los tests superados!\n");
}

int main(){
  test_string_len();
  return 0;
}