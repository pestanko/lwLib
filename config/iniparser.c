#include "iniparser.h"

#include <stdio.h>

int lwpars_ini_load(char *fpath, lwConfig *lwc)
{
    if(lwc == NULL || fpath == NULL)
    {
        return -1;
    }

    FILE *fin = fopen(fpath, "r");
    if(fin == NULL)
        return 1;

    lwConfigItem *curr_namespace = lwc->globalNamespace;

    while(!feof(fin))
    {
        char *line = lws_getline(fin);
        if(line == NULL)
            break;

        char *chr = strchr(line, ';'); // line contains comment
        if(chr != NULL) *chr = 0;

        if(strlen(line) == 0 || lws_empty_or_space(line))
        {
            free(line);
            continue;
        }

        chr = strchr(line, '[');
        if(chr != NULL)
        {
            char *end = strchr(line, ']');
            if(end == NULL)
            {
                free(line);
                perror("Wrong format.");
                fclose(fin);
                return 100;
            }
            *end = '\0';
            lwconf_set(lwc->globalNamespace, ++chr, NULL);
            curr_namespace = lwconf_item_get(lwc->globalNamespace, chr);
            free(line);
            line = NULL;
            continue;
        }
        chr = strchr(line, '=');
        if(chr == NULL) {
            chr = strchr(line, ':');
            if(chr == NULL)
            {
                free(line);
                fclose(fin);
                return 150;
            }
        }

        *chr = '\0';
        char *name = lws_trim(line);
        char *val = lws_strip(++chr);
        lwconf_set(curr_namespace, name, val);


        free(name);
        free(val);



        free(line);
        line = NULL;
    }

    fclose(fin);

    return 0;

}

int lwpars_int_save(char *fpath, lwConfig *lwc)
{
    if(lwc == NULL || fpath == NULL)
    {
        return -1;
    }

    FILE *fout = fopen(fpath, "w");
    if(fout == NULL)
        return 1;




    return 0;
}
