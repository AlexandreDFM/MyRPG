/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_sub_main_menus
*/

#include "rpg.h"

menuss *init_load_menu(wininf *inf, int menu_id)
{
    menuss *menu = malloc(sizeof(menuss));
    char **arr = my_strtwa(inf->atlases.menus[menu_id], ";\n");
    int offset = my_atoi(arr[3]) * 5 + 4;

}
