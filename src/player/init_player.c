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

void fill_stat(char **arr, player *p)
{
    int health = my_atoi(arr[6]) + rand() % 31;
    p->st.health = health * 3;
    p->st.max_health = health * 3;
    p->st.max_health_boost = 0;
    p->st.defense = my_atoi(arr[7]) + rand() % 31;
    p->st.def_boost = 0;
    p->st.attack = my_atoi(arr[8]) + rand() % 31;
    p->st.atk_boost = 0;
    p->st.spe_att = my_atoi(arr[9]) + rand() % 31;
    p->st.spe_atk_boost = 0;
    p->st.spe_def = my_atoi(arr[10]) + rand() % 31;
    p->st.spe_def_boost = 0;
    p->st.speed = my_atoi(arr[11]) + rand() % 31;
    p->st.speed_boost = 0;
    p->st.lvl = 5;
}

sfSprite *set_shadow(wininf inf, player *p, int id)
{
    if (id != 4) return NULL;
    sfSprite *shadow = NULL;
    if (p->r.width < 30) {
        shadow = atlas_to_sprite((sfIntRect)
        {745, 1087, 14, 16}, inf.atlases.atlas);
    } else {
        shadow = atlas_to_sprite((sfIntRect)
        {760, 1086, 22, 8}, inf.atlases.atlas);
    }
    return shadow;
}

player *init_player(wininf inf, int id)
{
    player *p = malloc(sizeof(player)); p->shiny = rand () % 10 == 1 ? 1 : 0;
    p->vel = (sfVector2f){0.0f, 0.0f}; p->animc = 0.0f; p->can_move = 1;
    p->target = (sfVector2f){0.0f, 0.0f}; p->attacking = 0;
    char **arr = my_strtwa(inf.atlases.pokemons_anim[id], ";\n");
    fill_stat(arr, p); int i = 0; for (; arr[i] != NULL; i++);
    int *arr1 = my_malloc(sizeof(int) * i); p->arrived = 0;
    for (int j = 0; j < i; j++) arr1[j] = my_atoi(arr[j]);
    char **arr2 = my_strtwa(inf.atlases.pokemons_rect[id], ";\n");
    int **rlist = get_player_rects(arr2); p->time = 0.0f;
    p->slist = arr1; p->rlist = rlist; p->direction = PNONE_DIRECTION;
    sfIntRect r = (sfIntRect) {arr1[1], arr1[2], arr1[5], arr1[4]};
    p->test = atlas_to_sprite(r, inf.atlases.atlas); p->offset = arr1[3];
    p->limit = (sfVector2i) {arr1[3] * rlist[5][0], arr1[3] * rlist[5][1]};
    p->r = (sfIntRect) {arr1[3] * rlist[5][0], 0, arr1[3], arr1[4]};
    p->speed = 120.0f; sfSprite_setOrigin(p->test, (sfVector2f){11.0f, 25.0f});
    sfSprite_setPosition(p->test, (sfVector2f){520.0f, 320.0f});
    sfVector2f np = {-1.0f, -1.0f}; p->nextpos = np; p->sentpos = np;
    sfSprite_setTextureRect(p->test, p->r); p->shadow = set_shadow(inf, p, id);
    p->equip_slot = NULL; p->equipped = 0;
    my_free_array(arr); my_free_array(arr2); return p;
}
