/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** update_playtime
*/

#include "rpg.h"

void update_playtime(wininf *inf)
{
    char *final = my_strdup("00:00:00");
    int tmpt = sfClock_getElapsedTime(inf->play_time).microseconds / 1000000;
    int hours = tmpt / 3600; int minutes = (tmpt % 3600) / 60;
    int seconds = (tmpt % 3600) % 60;
    final[0] = hours / 10 + '0'; final[1] = hours % 10 + '0';
    final[3] = minutes / 10 + '0'; final[4] = minutes % 10 + '0';
    final[6] = seconds / 10 + '0'; final[7] = seconds % 10 + '0';
    dline *poubelle = load_line(final, inf->ui.font, 15, inf);
    sfIntRect r; r.left = 0, r.top = 0;
    r.width = poubelle->steps[poubelle->max], r.height = poubelle->height;
    sfSprite_setTextureRect(poubelle->sp, r);
    sfVector2f old_pos = sfSprite_getPosition(inf->pause_menu->texts->data);
    inf->pause_menu->texts->data = poubelle->sp;
    sfSprite_setPosition(inf->pause_menu->texts->data, old_pos);
}
