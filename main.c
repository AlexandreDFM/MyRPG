/*
** EPITECH PROJECT, 2022
** main
** File description:
** Main of rpg
*/

#include "infos.h"
#include "scenes.h"

int main(int argc, char **argv)
{
    wininf *infos = create_window_infos();
    while (sfRenderWindow_isOpen(infos->win)) {
        update_events(infos);
        handle_scene(infos);
    }
    return 0;
}
