#include <stdio.h>
#include <math.h>
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

float mediana(float arr[], int length){
  float aux[length];
  for(int i = 0; i < length; i++){
    aux[i] = arr[i]; 
  }

  bubble_sort(aux, length);

  int idx = floor(length / 2);
  if(length % 2 != 0)
    return aux[idx];
  
  return (aux[idx - 1] + aux[idx]) / 2;
}

int main(){
  // Caso 1: Un solo elemento (Largo impar mínimo)
  float case1[] = {42.0};
  assert(fabs(mediana(case1, 1) - 42.0) < 0.001);

  // Caso 2: Dos elementos (Largo par mínimo)
  float case2[] = {10.0, 20.0};
  assert(fabs(mediana(case2, 2) - 15.0) < 0.001);

  // Caso 3: Valores negativos y cero
  float case3[] = {-10.5, -5.0, 0.0, 2.5, 10.0};
  assert(fabs(mediana(case3, 5) - 0.0) < 0.001);

  // Caso 4: Todos los elementos iguales
  float case4[] = {7.0, 7.0, 7.0, 7.0};
  assert(fabs(mediana(case4, 4) - 7.0) < 0.001);

  // Caso 5: Desordenado impar (La mediana real es 3.0)
  float case5[] = {5.0, 1.0, 3.0}; 
  // Si no ordenás, tu función devolverá 1.0 (erróneo).
  assert(fabs(mediana(case5, 3) - 3.0) < 0.001);

  // Caso 6: Desordenado par (La mediana real es promedio de 3.0 y 4.0 = 3.5)
  float case6[] = {10.0, 3.0, 1.0, 4.0}; 
  assert(fabs(mediana(case6, 4) - 3.5) < 0.001);
  return 0;
}

