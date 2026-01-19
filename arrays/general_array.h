#ifndef __GARRAY_H__
#define __GARRAY_H__

typedef struct _GeneralArray {
  void** arr;
  int size;
} *GeneralArray;

typedef void (* DestroyFunction) (void*);

GeneralArray general_array_create(int size);

void general_array_destroy(GeneralArray, DestroyFunction);

#endif