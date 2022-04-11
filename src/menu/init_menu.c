/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_menu
*/

#include "rpg.h"

void init_menu(sfVector2i size, sfVector2f pos, wininf *inf, int menu_id)
{
    menus menu;
    sfIntRect cursor = {0, 0 , 5, 5};
    menu.background = generate_textbox(size, inf->atlases.atlas);
    menu.cursor = atlas_to_sprite(cursor, inf->atlases.atlas);
    menu.choices = malloc(sizeof(list));
    menu.choices = init_circular(my_strtwa(inf->atlases.menus[menu_id], ";\n"), inf);
}
