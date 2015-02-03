#ifndef INIPARSER_H
#define INIPARSER_H
#include "config.h"


int lwpars_ini_load(char *fpath, lwConfig *lwc);
int lwpars_int_save(char *fpath, lwConfig *lwc);

#endif // INIPARSER_H
