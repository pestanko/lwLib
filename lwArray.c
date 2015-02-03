#include "lwArray.h"
#include <stdlib.h>
#include <string.h>

lwArray lwarr_sinit(void *arr, size_t size)
{
    lwArray a;
    a.container = arr;
    a.size = size;

    return a;
}

lwArray * lwarr_init(void *arr, size_t size)
{
    if(arr == NULL) return NULL;
    lwArray *a = (lwArray*) malloc(sizeof(lwArray));
    memcpy(a->container, arr, size);
    a->size = size;
    return a;
}

size_t lwarr_size(lwArray *arr)
{
    return arr->size;
}

void * lwarr_get(lwArray *arr, size_t index)
{
    if(index >= arr->size) return NULL;
    return  &(arr->container[index]);
}

