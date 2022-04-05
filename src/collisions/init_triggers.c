/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_triggers
*/

#include "rpg.h"

void create_triggers(wininf *inf)
{
    inf->triggers[0] = homeext_to_village;
    inf->triggers[1] = homeext_to_homeint;
    inf->triggers[2] = ta_mere;
    inf->triggers[3] = sleep_and_save;
    inf->triggers[4] = interact_pnj;
}

void homeext_to_village(wininf *win, player p)
{
    sfVector2f home = (sfVector2f){520.0f, 320.0f};
    sfVector2f village = (sfVector2f){25.0f, 320.0f};
    win->next_scene = win->c_scene == VILLAGE ? HOME : VILLAGE;
    win->next_pos = win->c_scene == VILLAGE ? home : village;
    win->change_scene = 1;
    win->transition = 1;
}

void homeext_to_homeint(wininf *win, player p)
{
    sfVector2f home = (sfVector2f){275.0f, 200.0f};
    sfVector2f interior = (sfVector2f){166.0f, 235.0f};
    win->next_scene = win->c_scene == HOME ? INTERIOR : HOME;
    win->next_pos = win->c_scene == INTERIOR ? home : interior;
    win->transition = 1;
    win->change_scene = 1;
}

void ta_mere(wininf *win, player p)
{
    my_printf("Eh non ta mère :D\n");
    sfVector2f mid = (sfVector2f){520.0f, 320.0f};
    win->next_scene = VILLAGE;
    win->next_pos = mid;
    win->transition = 1;
    win->change_scene = 1;
}

void interact_pnj(wininf *win, player p)
{
    float min = 200.f;
    pnj *closest = 0;
    list *l = win->scenes[win->c_scene].pnjs;
    for (list *t = l; t; t = t->next) {
        pnj *cp = t->data;
        float cmin = manhattan_distance(sfSprite_getPosition(p.test), cp->pos);
        if (cmin < min) {
            min = cmin;
            closest = cp;
        }
    }
    sfVector2f poubelle = sfView_getCenter(win->camera.view);
    poubelle.y += 45.0f;
    sfSprite_setPosition(win->ui.background, poubelle);
    FILE *f = fopen(closest->dialog, "r");
    char *str = 0;
    size_t len = 0;
    getline(&str, &len, f);
    str[my_strlen(str) - 1] = '\0';
    printf("Str: %s\n", str);
    dline *line = load_line(str, win->ui.font, FONT_SIZE);
    fclose(f);
    sfSprite *nsp = sfSprite_create();
    sfSprite_setTexture(nsp, line->img, sfFalse);
    poubelle.x -= sfSprite_getTextureRect(win->ui.background).width / 2 - 10;
    poubelle.y -= sfSprite_getTextureRect(win->ui.background).height / 2;
    poubelle.x = roundf(poubelle.x);
    poubelle.y = roundf(poubelle.y);
    sfSprite_setPosition(nsp, poubelle);
    win->ui.test = nsp;
    win->interacting = 1;
}

void sleep_and_save(wininf *win, player p)
{
    my_printf("Saving...\n");
    win->change_scene = 0;
    win->transition = 1;
}
