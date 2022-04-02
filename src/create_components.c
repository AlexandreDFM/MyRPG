/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_compoments
*/

#include "rpg.h"

components create_all_components(char **argv)
{
    components cps;
    cps.inf = create_window_infos(argv);
    cps.pla = init_player(cps.inf, my_atoi(argv[2]));
    cps.inf.camera.target = cps.pla.test;
    return cps;
}
