/*
** EPITECH PROJECT, 2022
** main
** File description:
** Init of window
*/

#include "infos.h"
#include "inputs.h"

void init_key_list(wininf *inf)
{
    const char *list[102] = {
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
    "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3",
    "4", "5", "6", "7", "8", "9", "Escape", "LControl", "LShift", "LAlt",
    "LSystem", "RControl", "RShift", "RAlt", "RSystem", "Menu", "LBracket",
    "RBracket", "SemiColon", "Comma", "Period", "Quote", "Slash", "BackSlash",
    "Tilde", "Equal", "Hyphen", "Space", "Enter", "BackSpace", "Tab", "PageUp",
    "PageDown", "End", "Home", "Insert", "Delete", "Add", "Subtract",
    "Multiply", "Divide", "Arrow Left", "Arrow Right", "Arrow Up",
    "Arrow Down", "Numpad 0", "Numpad 1",
    "Numpad 2", "Numpad 3", "Numpad 4", "Numpad 5", "Numpad 6", "Numpad 7",
    "Numpad 8", "Numpad 9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8",
    "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause"};
    inf->key_list = malloc(sizeof(char *) * 102);
    for (int i = 0; i < 101; i++)
        inf->key_list[i] = my_strdup((char *)list[i]);
}

wininf create_window_infos(int ac, char **av)
{
    srand(time(0));
    wininf inf; inf.lang = ENGLISH;
    inf.settings = init_settings();
    inf.net = init_network();
    get_settings_flags(ac, av, &inf);
    inf.mode = (sfVideoMode){1920, 1080, 32};
    inf.win = sfRenderWindow_create(inf.mode, WINDOW_NAME, sfClose, NULL);
    inf.c_scene = QUIZ;
    inf.interacting = 0;
    init_times(&inf);
    create_atlases(&inf);
    init_inputs(&inf);
    inf.scenes[0] = create_home(&inf, inf.settings->house);
    inf.scenes[1] = create_static_env(&inf, 0);
    inf.scenes[3] = create_static_env(&inf, 6);
    inf.scenes[4] = create_static_env(&inf, 2);
    inf.scenes[5] = create_static_env(&inf, 4);
    inf.scenes[2] = create_static_env(&inf, 6 + inf.settings->house * 2);
    inf.camera = init_camera(inf);
    create_triggers(&inf);
    inf.transition = 0;
    inf.change_scene = 0;
    dungeon d; d.img = sfImage_createFromFile("result8.png"); d.in = 0;
    inf.dungeon = d;
    inf.transi = sfRectangleShape_create();
    sfRectangleShape_setSize(inf.transi, (sfVector2f){inf.mode.width,
        inf.mode.height});
    sfRectangleShape_setFillColor(inf.transi,
        sfColor_fromRGBA(0, 0, 0, 0));
    sfRectangleShape_setOrigin(inf.transi,
    (sfVector2f){inf.mode.width / 2.0f, inf.mode.height / 2.0f});
    init_textbox(&inf);
    inf.main_menu = init_all_menus(&inf, MAIN_IDX, 1);
    init_main_menu_pointers(&inf);
    inf.load_menu = init_all_menus(&inf, LOAD_IDX, 0);
    init_load_pointers(&inf);
    inf.options_menu = init_all_menus(&inf, OPTIONS_IDX, 0);
    inf.change_keys_menu = init_all_menus(&inf,KEYBINDS_IDX, 0);                                                                                                                                                                                                         inf.options_menu = init_all_menus(&inf, OPTIONS_IDX, 0);
    inf.pause_menu = init_ig_menus(&inf, PAUSE_VILLAGE_IDX, 0);
    inf.others_menu = init_ig_menus(&inf, OTHERS_IDX, 0);
    init_options_pointers(&inf);
    inf.c_menu = NONE;
    inf.waiting_key = 0;
    inf.current_menu = inf.main_menu;
    inf.prev_menu = NULL;
    inf.vol_music = 100;
    inf.vol_sound = 100;
    inf.net->timeout.microseconds = 5000;
    inf.intro = NULL; inf.ditto = NULL; inf.dream = NULL;
    inf.quiz = NULL;
    inf.playtime = load_line("VOID", inf.ui.font, FONT_SIZE, &inf);
    inf.pressed = 0;
    sfRenderWindow_setFramerateLimit(inf.win, inf.settings->c_fps < 5 ?
    my_atoi(inf.settings->fps[inf.settings->c_fps]) : 0);
    sfText_setString(
        ((choices *)inf.options_menu->choices->prev->prev->prev->data)->choice
        , inf.settings->fps[inf.settings->c_fps]);
    init_key_list(&inf); inf.key_change = -1; inf.play_time = sfClock_create();
    set_pokemon(&inf);
    return inf;
}
