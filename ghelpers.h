#ifndef __G_HELPERS_H__
#define __G_HELPERS_H__
typedef void (*FuncionDestructora) (void*);
typedef void (*FuncionVisitante) (void*);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);
typedef int (*FuncionComparadora) (void*, void*);
typedef void* (*FuncionCopiadora) (void*);
#endif
