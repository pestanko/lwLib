#ifndef LWARRAY_H
#define LWARRAY_H

#include <stdlib.h>
#include <string.h>


struct lwArray_t
{
    void *container;
    size_t size;
};

typedef struct lwArray_t lwArray;

lwArray lwarr_sinit(void *arr, size_t size);

lwArray * lwarr_init(void *arr, size_t size);

size_t lwarr_size(lwArray *arr);
void * lwarr_get(lwArray *arr, size_t index);


#endif // LWARRAY_H
