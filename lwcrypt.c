#include "lwcrypt.h"

#include <stdint.h>


int lwcrypt_simple_xor(void *source, void *key, void *result, size_t size, size_t keySize)
{
    if(key == NULL || source == NULL) return -1;
    uint8_t *byteKey = (uint8_t*) key,
            *byteSource = (uint8_t*) source;
    uint8_t *key_orig = (uint8_t*) key,
            *byteRes = (uint8_t*) result;
    for(size_t i = 0; i < size; i++)
    {
        if(byteKey == (key_orig + keySize) )
            byteKey = key_orig;

        byteRes[i] = (uint8_t) ((char) byteSource[i] ^ (char) *byteKey);
        byteKey++;
    }
    return 0;
}


int lwcrypt_simple_xor_str(char *source, void *key ,char *result, size_t keySize)
{
    int slen = strlen(source);
    int res = lwcrypt_simple_xor(source, key, result, slen,  keySize);
    return res;
}

int lwcrypt_simple_xor_block(void *source, void *key, void *result, size_t size_data, size_t keySize ,size_t block)
{
    if(!(source && key && result))
        return -1;



    return 0;
}



int gen_random_string(char *str, size_t size)
{
    for(size_t i = 0 ; i < size; i++)
    {
        str[i] = (char) rand() % 95 + 32;
    }
    str[size] = '\0';


    return 0;
}


