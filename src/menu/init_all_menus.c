/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_all_menus
*/

#include "rpg.h"

menus *init_all_menus(wininf *inf, int menu_id)
{
    menus *menu = malloc(sizeof(menus));
    char **arr = my_strtwa(inf->atlases.menus[menu_id], ";\n");
    
}
