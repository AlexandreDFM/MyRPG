/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** add_pnjs
*/

#include "rpg.h"

void add_pnjs(atlases atlas, int idx, scene *s)
{
    char **arr = my_strtwa(atlas.collisions[idx], ";\n");
    for (int i = 0; arr[i]; i++) {
        if (!my_strcmp(arr[i], "PNJ")) {
            create_pnj(atlas.pnjs[my_atoi(arr[i + 1])], s, atlas);
        }
    }
}

void create_pnj(char *line, scene *s, atlases atlas)
{
    char **arr = my_strtwa(line, ";\n");
    place_decorations(line, atlas.atlas, atlas.statics, &(s->animated));
    pnj *pnj_s = my_malloc(sizeof(pnj));
    pnj_s->ent = my_malloc(sizeof(entity));
    pnj_s->ent = (entity*)s->animated->data;
    pnj_s->pos = sfSprite_getPosition(pnj_s->ent->sp);
    pnj_s->dialog = my_strdup(arr[3], my_malloc);
    list *nl = my_malloc(sizeof(list));
    nl->data = pnj_s;
    nl->next = s->pnjs;
    s->pnjs = nl;
    my_free_array(arr);
}
