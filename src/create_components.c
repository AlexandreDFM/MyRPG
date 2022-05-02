/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_compoments
*/

#include "rpg.h"

components create_all_components(int ac, char **argv)
{
    components cps;
    cps.inf = create_window_infos(ac, argv);
    cps.pla = init_player(cps.inf, cps.inf.settings->pokemon);
    cps.inf.camera.target = cps.pla->test;
    return cps;
}
