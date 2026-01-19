#include <stdio.h>
#include <assert.h>

int string_len(char* str){
  int count = 0, i = 0;
  while(str[i] != '\0'){
    printf("%c\n", str[i]);
    count++;
    i++;
  }
  return count;
}

int main(){
  char str1[] = "Hola";
  char str2[] = "Lucas";
  char str3[] = "lcc";
  char str4[] = "Una frase más larga!";
  return 0;
}