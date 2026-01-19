#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void bubble_sort(float arreglo[], int longitud) {
  for (int iter = 0 ; iter < longitud - 1 ; iter++) {
    for (int i = 0 ; i < longitud - iter - 1; i++) {
      if (arreglo[i] > arreglo[i + 1]) {
        float aux = arreglo[i];
        arreglo[i] = arreglo[i + 1];
        arreglo[i + 1] = aux;
      }
    }
  }
}

float mediana(float *arreglo, int longitud){
  int mitad;
  float resultado;
  float* sortedArray = malloc(longitud * sizeof(float));
  
  for(int i = 0; i < longitud; i++){
    sortedArray[i] = arreglo[i];
  }
  bubble_sort(sortedArray, longitud);

  if (longitud % 2 == 0) {
    mitad = longitud / 2;
    resultado = (sortedArray[mitad - 1] + sortedArray[mitad]) / 2; 
  }else{
    mitad = (longitud - 1) / 2;
    resultado = sortedArray[mitad];
  }
  free(sortedArray);
  return (float) resultado;
}

int main() {
  float arr1[] = {-1.0, 2.2, 2.9, 3.1, 3.5}; 
  float arr2[] = {-1.0, 2.2, 2.9, 3.1}; 
  float result1 = 2.90;
  float result2 = (2.2f + 2.9f) / 2;
  /* printf("Mediana de arr1: %.2f\n", mediana(arr1, 5));
  printf("Mediana de arr2: %.30f\nresult2:%.30f\n", mediana(arr2, 4), result2); */
  assert(mediana(arr1, 5) == result1);
  assert(mediana(arr2, 4) == result2);
  
  return 0;
}