#include <assert.h>
#include <stdio.h>

int string_compare(char* str1, char* str2){
  while(*str1 == *str2 && *str1 != '\0' && *str2 != '\0'){
    str1++;
    str2++;
  }

  if(*str1 < *str2){
    return -1;
  }
  if(*str1 > *str2){
    return 1;
  }
  return 0;
}

void test_string_compare() {
    // Caso 1: Cadenas idénticas
    assert(string_compare("rosario", "rosario") == 0);

    // Caso 2: Cadenas vacías
    assert(string_compare("", "") == 0);

    // Caso 3: str1 es menor alfabéticamente
    // 'a' es menor que 'b'
    assert(string_compare("abc", "abd") == -1);

    // Caso 4: str1 es mayor alfabéticamente
    assert(string_compare("pala", "paca") == 1);

    // Caso 5: Una es prefijo de la otra (la más corta es menor)
    assert(string_compare("hola", "holanda") == -1);
    assert(string_compare("holanda", "hola") == 1);

    // Caso 6: Diferencia por mayúsculas (ASCII: 'A' = 65, 'a' = 97)
    // 'A' es menor que 'a'
    assert(string_compare("Apple", "apple") == -1);

    // Caso 7: str1 es un espacio vacío vs un carácter
    assert(string_compare("", "z") == -1);
    assert(string_compare("z", "") == 1);

    puts("Yay! Todo los test del ejercicio d pasaron!!!");
}

int main(){
  test_string_compare();
  return 0;
}