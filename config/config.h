#ifndef CONFIG_H
#define CONFIG_H

#include "../lwstring.h"

#define LWCONF_ALLOC_SIZE 50
#define LWCONF_ALLOC_MULT 2
#define LWCONF_NAMESPACE_SEPARATOR '.'



typedef struct lwConfigItem_t
{
    struct lwConfigItem_t *prev;
    char *name;
    char *val;
    size_t size;
    size_t alloc_size;
    struct lwConfigItem_t **items;
}lwConfigItem;


typedef struct lwConfig_t
{
    lwConfigItem *globalNamespace;
} lwConfig;


/* Inicialization */
lwConfigItem * lwconf_item_init(lwConfigItem *nmspc, char *name, char *val);
int lwconf_init(lwConfig * conf);


/* Setters */
int lwconf_set(lwConfigItem *lwnmspc, char *name, char *val);
int lwconf_setg(lwConfig *lwc, char *name, char *val);

/*Getters*/
lwConfigItem *lwconf_item_get(lwConfigItem *lwc, char *name);
lwConfigItem *lwconf_item_getg(lwConfig *lwc, char *name);
char *lwconf_get(lwConfigItem *lwc, char *name);
char *lwconf_getg(lwConfig *lwc, char *name);


lwConfigItem *lwconf_item_find(lwConfigItem *lwc, char * name);

int lwconf_remove(lwConfig *lwc, char *name, char *val);


/* Destruction*/
int lwconf_destroy(lwConfig *conf);
int lwconf_item_destroy(lwConfigItem *item);


/* Print */

void lwconf_print_subtree(lwConfigItem *lwc);
char * lwconf_get_path(lwConfigItem *lwc);




#endif // CONFIG_H
