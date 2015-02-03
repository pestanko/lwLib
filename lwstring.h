#ifndef LWSTRING_H
#define LWSTRING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


char *lws_create(size_t len);

char *lws_copy(char *str);
char *lws_append(char *s1, char *s2);
char *lws_prepend(char *s1, char *s2);
char *lws_fill(char *str, char f);
char *lws_genrandom(size_t size);

size_t lws_sizea(char *s);
size_t lws_size2a(char *str1, char *str2);

char *lws_search(char *str, char *sub);
int lws_search_pos(char *str, char *sub);
char *lws_searchc(char *str, char sub);
int lws_searchc_pos(char *str, char sub);

char *lws_getline(FILE *in);
int lws_empty_or_space(char * str);
char *lws_trim(char *str);
char *lws_strip(char *str);

#endif // LWSTRING_H
