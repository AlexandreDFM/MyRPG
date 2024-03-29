/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_static_anim
*/

#include "rpg.h"

void test_static_anim(char *name, float *size, char **csv, int *i)
{
    my_printf(stdout, "\tLoading ");
    if (name[0] == '_') {
        (*size) *= -1.0f;
        name += 1;
        my_printf(stdout, "Reversed ");
    }
    my_printf(stdout, "%s ", name);
    for (; csv[*i]; (*i) = *i + 1) {
        int len = my_strlen(csv[*i]);
        if (!my_strncmp(name, csv[*i], len))
            break;
    }
}

void create_static_anim(sfImage *atlas, char *name, list **l, char **csv)
{
    int i = 0; float size = 1.0f; test_static_anim(name, &size, csv, &i);
    char **args = my_strtwa(csv[i], ";\n");
    entity *ne = my_malloc(sizeof(entity));
    ne->width = my_atoi(args[3]);
    sfIntRect r = (sfIntRect){my_atoi(args[1]), my_atoi(args[2]),
        my_atoi(args[5]) + ne->width, my_atoi(args[4])};
    ne->max = my_atoi(args[5]);
    ne->sp = atlas_to_sprite(r, atlas);
    sfSprite_setScale(ne->sp, (sfVector2f){size, 1.0f});
    if (my_strcmp(name, "LordDitto") == 0)
        sfSprite_setScale(ne->sp, (sfVector2f){0.2, 0.2});
    if (my_strcmp(name, "LittleDitto") == 0)
        sfSprite_setScale(ne->sp, (sfVector2f){0.1, 0.1});
    ne->sign = 1; ne->loop_type = my_atoi(args[6]);
    add_to_list(l, ne);
    r.width = ne->width;
    int rdm = ne->max ? rand() % ne->max / ne->width : 0;
    r.top = 0; r.left = ne->width * rdm;
    ne->rect = r; my_free_array(args); sfSprite_setTextureRect(ne->sp, r);
}
