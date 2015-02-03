#ifndef LWBASE64_H
#define LWBASE64_H

#include <string.h>

inline size_t base64encode_size(size_t dataLen) { return ((dataLen/3) + 1) * 4; }
inline size_t base64decode_size(size_t encLen) {return ((encLen/4) + 1) * 3; }



int base64decode (char *in, size_t inLen, unsigned char *out, size_t *outLen);
int base64encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize);




#endif // LWBASE64_H
