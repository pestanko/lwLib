#ifndef LWCRYPT_H
#define LWCRYPT_H

#include <string.h>
#include <stdlib.h>


int lwcrypt_simple_xor(void * source, void * key ,void * result, size_t size, size_t keySize);
int lwcrypt_simple_xor_str(char *source, void *key ,char *result, size_t keySize);
int lwcrypt_simple_xor_block(void *source, void *key, void *result, size_t size_data, size_t keySize ,size_t block);

int gen_random_string(char *str, size_t size);




#endif // LWCRYPT_H
