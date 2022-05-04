/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** inti_player
*/

#include "rpg.h"

int **get_player_rects(char **arr)
{
    int i = 0; for (; arr[i] != NULL; i++);
    int **rects = my_malloc(sizeof(int *) * i);
    for (int j = 0; j < i; j++) {
        rects[j] = my_malloc(sizeof(int) * 2);
        char *firstnb = my_strdup_to_char(arr[j], "-");
        char *secondnb = my_slice_array(0, arr[j], pos_char(arr[j], "-") + 1);
        int nb1 = my_atoi(firstnb); int nb2 = my_atoi(secondnb);
        rects[j][0] = nb1; rects[j][1] = nb2;
        free(firstnb); free(secondnb);
    }
    return rects;
}

player *init_player(wininf inf, int id)
{
    player *p = my_malloc(sizeof(player));p->shiny = rand () % 10 == 1 ? 1 : 0;
    p->vel = (sfVector2f){0.0f, 0.0f}; p->animc = 0.0f;
    char **arr = my_strtwa(inf.atlases.pokemons_anim[id], ";\n");
    int i = 0; for (; arr[i] != NULL; i++);
    int *arr1 = my_malloc(sizeof(int) * i);
    for (int j = 0; j < i; j++) arr1[j] = my_atoi(arr[j]);
    char **arr2 = my_strtwa(inf.atlases.pokemons_rect[id], ";\n");
    int **rlist = get_player_rects(arr2);
    p->slist = arr1; p->rlist = rlist; p->direction = PNONE_DIRECTION;
    sfIntRect r = (sfIntRect) {arr1[1], arr1[2], arr1[5], arr1[4]};
    p->test = atlas_to_sprite(r, inf.atlases.atlas); p->offset = arr1[3];
    p->r = (sfIntRect) {0, 0, arr1[3], arr1[4]};
    p->limit = (sfVector2i) {arr1[3] * rlist[5][0], arr1[3] * rlist[5][1]};
    p->speed = 120.0f; p->vel = (sfVector2f){0.0f, 0.0f};
    sfSprite_setOrigin(p->test, (sfVector2f){11.0f, 25.0f});
    sfSprite_setPosition(p->test, (sfVector2f){520.0f, 320.0f});
    p->nextpos = (sfVector2f){-1.0f, -1.0f};
    init_inventory(p, 10);
    p->sentpos = (sfVector2f){-1.0f, -1.0f}; p->time = 0.0f;
    sfSprite_setTextureRect(p->test, p->r);
    my_free_array(arr); my_free_array(arr2); return p;
}
