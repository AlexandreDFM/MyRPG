/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_static_anim
*/

#include "rpg.h"

void create_static_anim(sfImage *atlas, char *name, list **l, char **csv)
{
    int i = 0;
    float size = 1.0f;
    printf("\tLoading ");
    if (name[0] == '_') {
        size *= -1.0f;
        name += 1;
        printf("Reversed ");
    }
    printf("%s...\n", name);
    for (; csv[i]; i++) {
        int len = my_strlen(csv[i]);
        if (!my_strncmp(name, csv[i], len))
            break;
    }
    char **args = my_strtwa(csv[i], ";\n");
    entity *ne = malloc(sizeof(entity));
    ne->width = my_atoi(args[3]);
    sfIntRect r = (sfIntRect){my_atoi(args[1]), my_atoi(args[2]),
        my_atoi(args[5]) + ne->width, my_atoi(args[4])};
    ne->max = my_atoi(args[5]);
    ne->sp = atlas_to_sprite(r, atlas);
    sfSprite_setScale(ne->sp, (sfVector2f){size, 1.0f});
    ne->sign = 1;
    ne->loop_type = my_atoi(args[6]);
    add_to_list(l, ne);
    r.width = ne->width;
    r.top = 0; r.left = ne->width * (rand() % (ne->max / ne->width));
    ne->rect = r;
    sfSprite_setTextureRect(ne->sp, r);
}