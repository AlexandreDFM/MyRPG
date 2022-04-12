/*
** EPITECH PROJECT, 2022
** main
** File description:
** Init of window
*/

#include "infos.h"
#include "inputs.h"

wininf create_window_infos(int ac, char **av)
{
    srand(time(0));
    wininf inf;
    inf.settings = init_settings();
    inf.net = init_network();
    get_settings_flags(ac, av, &inf);
    inf.mode = (sfVideoMode){1920, 1080, 32};
    inf.win = sfRenderWindow_create(inf.mode, WINDOW_NAME, sfClose, NULL);
    inf.c_scene = MAIN_MENU;
    inf.interacting = 0;
    init_times(&inf);
    create_atlases(&inf);
    init_inputs(&inf);
    inf.scenes[0] = create_home(&inf, inf.settings->house);
    inf.scenes[1] = create_static_environment(&inf, 0);
    inf.scenes[3] = create_static_environment(&inf, 6);
    inf.scenes[4] = create_static_environment(&inf, 2);
    inf.scenes[5] = create_static_environment(&inf, 4);
    inf.scenes[2] = create_static_environment(&inf, 6 + inf.settings->house * 2);
    inf.camera = init_camera(inf);
    create_triggers(&inf);
    inf.transition = 0; inf.change_scene = 0;
    inf.transition_rect = sfRectangleShape_create();
    sfRectangleShape_setSize(inf.transition_rect, (sfVector2f){inf.mode.width,
        inf.mode.height});
    sfRectangleShape_setFillColor(inf.transition_rect,
        sfColor_fromRGBA(0, 0, 0, 0));
    sfRectangleShape_setOrigin(inf.transition_rect,
    (sfVector2f){inf.mode.width / 2.0f, inf.mode.height / 2.0f});
    init_textbox(&inf);
    inf.menu_padding = 40;
    inf.main_menu = init_menu(&inf, 0);
    init_main_menu_pointers(&inf);
    inf.load_menu = init_load_menu(&inf, 1);
    inf.c_menu = NONE;
    inf.current_menu = inf.main_menu;
    init_load_pointers(&inf);
    return inf;
}
