#include <assert.h>
#include <string.h>
#include <stdio.h>

void string_unir(char** arregloString, int n, char* sep, char* res){
  int lengthSep = strlen(sep);
  for(int i = 0; i < n; i++){
    char* word = (char*) *(arregloString + i);
    int length = strlen(word);
    for(int j = 0; j < length; j++){
      *res++ = *word++;
    }
    if(i == n - 1) continue;
    char* sepAux = sep;
    for(int j = 0; j < lengthSep; j++){
      *res++ = *sepAux++;
    }
  }
  *res = '\0';
} 

void test_string_unir() {
  char res[100];

  // Caso 1: Varios strings con separador de un carácter
  char* arr1[] = {"Hola", "mundo", "C"};
  string_unir(arr1, 3, " ", res);
  assert(strcmp(res, "Hola mundo C") == 0);

  // Caso 2: Un solo string (no debe incluir el separador)
  char* arr2[] = {"Solo"};
  string_unir(arr2, 1, "-", res);
  assert(strcmp(res, "Solo") == 0);

  // Caso 3: Separador de varios caracteres
  char* arr3[] = {"Rosario", "Santa Fe"};
  string_unir(arr3, 2, " -> ", res);
  assert(strcmp(res, "Rosario -> Santa Fe") == 0);

  // Caso 4: Strings vacíos en el arreglo
  char* arr4[] = {"", "medio", ""};
  string_unir(arr4, 3, "*", res);
  assert(strcmp(res, "*medio*") == 0);

  // Caso 5: Separador vacío
  char* arr5[] = {"A", "B", "C"};
  string_unir(arr5, 3, "", res);
  assert(strcmp(res, "ABC") == 0);

  // Caso 6: n = 0 (debe resultar en una cadena vacía)
  char* arr6[] = {"No", "importa"};
  string_unir(arr6, 0, "sep", res);
  assert(strcmp(res, "") == 0);

  // Caso 7: Verificación de nulo final (ensuciando el buffer antes)
  memset(res, 'X', 100);
  char* arr7[] = {"Test", "Final"};
  string_unir(arr7, 2, "!", res);
  assert(strcmp(res, "Test!Final") == 0);
  assert(res[10] == '\0'); 

  puts("Yay");
}

int main() {
  test_string_unir();
  return 0;
}