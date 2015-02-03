#include "config.h"

lwConfigItem * lwconf_item_init(lwConfigItem *parent, char *name, char *val)
{
    lwConfigItem *item = (lwConfigItem*) malloc(sizeof(lwConfigItem));
    if(!item) return NULL;
    item->prev = parent;
    item->name = lws_copy(name);
    item->val = lws_copy(val);
    item->alloc_size = LWCONF_ALLOC_SIZE;
    item->size = 0;
    item->items = NULL;
    return item;
}

int lwconf_init(lwConfig * conf)
{
    if(!conf) return -1;

    conf->globalNamespace = lwconf_item_init(NULL, NULL, NULL);
    if(conf->globalNamespace == NULL)
        return -10;

    return 0;
}



int lwconf_destroy(lwConfig *conf){
    if(conf == NULL) return -1;
    if(conf->globalNamespace == NULL)
        return 0;

    lwconf_item_destroy(conf->globalNamespace);
    free(conf->globalNamespace);
    conf->globalNamespace = NULL;
    return 0;
}

int lwconf_item_destroy(lwConfigItem *item)
{
    if(item == NULL)
        return -1;
    //printf("Destroy: %s - %s\n", item->name, item->val);
    free(item->name);
    free(item->val);

    for(size_t i =0;  i < item->size; i++)
    {
       lwconf_item_destroy(item->items[i]);
       free(item->items[i]);
    }

    free(item->items);
    item->val = NULL;
    item->name = NULL;
    item->prev = NULL;
    item->items = NULL;
    return 0;
}



int lwconf_set(lwConfigItem *lwnmspc, char *name, char *val)
{
    if(lwnmspc == NULL) // Only global namespace
        return -1;

    if(lwnmspc->items == NULL && lwnmspc->size == 0)
    {
        lwnmspc->items = (lwConfigItem **) malloc(sizeof(lwConfigItem*) * lwnmspc->alloc_size);
    }


    lwConfigItem *item = lwconf_item_get(lwnmspc, name); // get Item Pointer
    if(item != NULL) // only updating ~> not adding
    {
        free(item->val); // free whatever before
        item->val = lws_copy(val); // update
        return 0;
    }

    item = lwconf_item_init(lwnmspc, name, val);
    if(item == NULL)
        return -2;

    size_t tmp_size = lwnmspc->alloc_size;
    if((lwnmspc->size+1) >= lwnmspc->alloc_size)
    {
        lwnmspc->alloc_size *=LWCONF_ALLOC_MULT;
        if(lwnmspc->alloc_size < tmp_size)
        {
            return 100;
        }
        lwnmspc->items = (lwConfigItem**) realloc(lwnmspc->items, lwnmspc->alloc_size * sizeof(lwConfigItem*));
        if(lwnmspc->items == NULL)
            return -10;
    }
    lwnmspc->items[lwnmspc->size] = item;
    (lwnmspc->size)++;
    return 0;
}

int lwconf_setg(lwConfig *lwc, char *name, char *val)
{
    // TODO
    if(name == NULL || val == NULL) return 0;
    lwConfigItem *item = lwc->globalNamespace;
    if(item == NULL) return 0;
    return 0;
}

lwConfigItem *lwconf_item_get(lwConfigItem *lwc, char *name)
{
    if(lwc == NULL || name == NULL) // Only global namespace
        return NULL;
    for(size_t i = 0 ; i < lwc->size; i++)
    {
        if(strcmp((lwc->items[i])->name , name) == 0)
            return lwc->items[i];
    }
    return NULL;
}

lwConfigItem *lwconf_item_getg(lwConfig *lwc, char *name)
{
    return lwconf_item_find(lwc->globalNamespace, name);
}

char *lwconf_get(lwConfigItem *lwc, char *name)
{
    return lwconf_item_get(lwc, name)->val;
}

char *lwconf_getg(lwConfig *lwc, char *name)
{
    return lwconf_item_getg(lwc, name)->val;
}


int lwconf_remove(lwConfig *lwc, char *name, char *val)
{
    if(lwc == NULL || name == NULL || val == NULL) return 1;
    // TODO
    return 0;
}


lwConfigItem * lwconf_item_find(lwConfigItem *lwc, char *name)
{
    if(lwc == NULL || name == NULL)
        return NULL;
    char *next = strchr(name, LWCONF_NAMESPACE_SEPARATOR);
    if(next == NULL)
        return lwconf_item_get(lwc, name);
    size_t len = next - name;


    char nmspc[len + 1];
    strncpy(nmspc, name, len);
    next++;
    lwConfigItem *nm = lwconf_item_get(lwc, nmspc);
    if(nm == NULL)
        return NULL;
    return lwconf_item_find(nm, next);

}

void lwconf_print_subtree(lwConfigItem *lwc)
{
    if(lwc == NULL) return;

    char *path = lwconf_get_path(lwc);
    if(lwc->val != NULL)
        printf("%s = %s\n", path, lwc->val);
    free(path);
    path = NULL;
    for(size_t i = 0 ; i < lwc->size; i++)
    {
        lwconf_print_subtree(lwc->items[i]);
    }
}


char * lwconf_get_path(lwConfigItem *lwc)
{
    if(lwc == NULL)
        return NULL;
    char *res = lwconf_get_path(lwc->prev);

    size_t len = 0;
    if(res != NULL) len += strlen(res);
    if(lwc->name != NULL ) len += strlen(lwc->name);
    if(len == 0) return NULL;
    len += 2;
    char *str = lws_create(len);
    if(str == NULL)
        return NULL;
    *str = '\0';
    if(res != NULL)
        strcpy(str, res);
    if(res != NULL)
        strcat(str, ".");
    if(lwc->name!= NULL)
        strcat(str, lwc->name);

    free(res);
    return str;
}
