#ifndef TABLE_POINTERS_H
#define TABLE_POINTERS_H

#define TRUE 1
#define FALSE 0

typedef void * pointer_t;
typedef unsigned char bool_t;

typedef struct _table_pointers
{
    pointer_t * pointers;
    bool_t allowed;

} tab_pointers;


tab_pointers table_pointers;


bool_t lwTp_isAllowed()
{
    return table_pointers.allowed;
}

bool_t lwTp_allow(bool_t allow)
{
    return table_pointers.allowed = allow;
}

bool_t lwTp_free(pointer_t item)
{
    pointer_t lwTp_find(item);

}



#endif // TABLE_POINTERS_H
