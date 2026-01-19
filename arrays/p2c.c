#include <assert.h>
#include <string.h>
#include <stdio.h>

int string_concat(char* str, char* str1, int copy){
  str += strlen(str);
  int loop = 0;
  while(*str1 != '\0' && loop < copy){
    *str = *str1;
    str++;
    str1++;
    loop++;
  }
  *str = '\0';
  return loop;
}

void test_string_concat() {
    // Caso 1: Concatenación completa (max > longitud de str2)
    char buffer[20];
    
    // Llenamos el buffer de basura (caracteres 'X') 
    // para que no haya nulos "de regalo"
    memset(buffer, 'X', 20); 
    
    // Ahora ponemos el string inicial manualmente
    buffer[0] = 'H'; buffer[1] = 'o'; buffer[2] = 'l'; buffer[3] = 'a';
    buffer[4] = '\0'; 

    string_concat(buffer, " Mundo", 10);

    // Si tu función no pone el '\0', strcmp va a seguir leyendo 
    // las 'X' que pusimos antes y el assert va a explotar.
    assert(strcmp(buffer, "Hola Mundo") == 0);

    // Caso 2: Concatenación parcial (max < longitud de str2)
    char buffer2[20] = "Buenas";
    int copiados2 = string_concat(buffer2, " Noches", 3);
    // Solo debe copiar " No" (3 caracteres: espacio, N, o)
    assert(strcmp(buffer2, "Buenas No") == 0);
    assert(copiados2 == 3);

    // Caso 3: max es exactamente la longitud de str2
    char buffer3[20] = "C";
    int copiados3 = string_concat(buffer3, "++", 2);
    assert(strcmp(buffer3, "C++") == 0);
    assert(copiados3 == 2);

    // Caso 4: max es 0 (no debe copiar nada)
    char buffer4[20] = "Inmutable";
    int copiados4 = string_concat(buffer4, " Cambio", 0);
    assert(strcmp(buffer4, "Inmutable") == 0);
    assert(copiados4 == 0);

    // Caso 5: str1 está vacía inicialmente
    char buffer5[20] = "";
    int copiados5 = string_concat(buffer5, "Software", 5);
    assert(strcmp(buffer5, "Softw") == 0);
    assert(copiados5 == 5);

    // Caso 6: str2 está vacía
    char buffer6[20] = "Rosario";
    int copiados6 = string_concat(buffer6, "", 5);
    assert(strcmp(buffer6, "Rosario") == 0);
    assert(copiados6 == 0);

    printf("Yay!, todos los test pasaron!!!\n");
}

int main(){
  test_string_concat();
  return 0;
}