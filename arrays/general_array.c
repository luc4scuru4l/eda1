#include <stdlib.h>
#include "general_array.h"

GeneralArray general_array_create(int size){
  if(size <= 0)
    return NULL;

  GeneralArray g = malloc(sizeof(struct _GeneralArray));
  
  if(g == NULL)
    return NULL;
  
  g->size = size;
  g->arr = malloc(sizeof(void *) * size);
  if(g->arr == NULL){
    free(g);
    return NULL;
  }

  for(int i = 0; i < size; i++)
    g->arr[i] = NULL;
  
  return g;
}

void general_array_destroy(GeneralArray* array, DestroyFunction destroy){
  if(array == NULL || *array == NULL || destroy == NULL)
    return;
  GeneralArray arr = *array; 
  if(arr->arr != NULL){
    for(int i = 0; i < arr->size; i ++)
      if(arr->arr[i] != NULL)
        destroy(arr->arr[i]);
  }
  free(arr->arr);
  free(arr);
}