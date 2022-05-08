/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_hud
*/

#include "rpg.h"

void init_hud(wininf *inf)
{
    sfIntRect rect[4] = {{820, 1157, 10, 8}, {831, 1157, 13, 8},
    {844, 1157, 6, 8}, {820, 1166, 30, 6}};
    for (int i = 0; i < 4; i++) {
        inf->ui.hud[i] = my_sprite();
        sfTexture *tex = sfTexture_createFromImage(inf->atlases.atlas,
        &(rect[i]));
        sfSprite_setTexture(inf->ui.hud[i], tex, sfTrue);
    }
    for (int i = 0; i < 2; i++) {
        inf->ui.hp[i] = my_text();
        sfText_setCharacterSize(inf->ui.hp[i], 50);
        sfText_setScale(inf->ui.hp[i], (sfVector2f){0.25, 0.25});
        sfText_setFont(inf->ui.hp[i], inf->ui.font);
        sfText_setColor(inf->ui.hp[i], sfColor_fromRGB(248, 128, 88));
    }
    inf->ui.lvl = my_text(); sfText_setCharacterSize(inf->ui.lvl, 50);
    sfText_setScale(inf->ui.lvl, (sfVector2f){0.25, 0.25});
    sfText_setFont(inf->ui.lvl, inf->ui.font);
}
