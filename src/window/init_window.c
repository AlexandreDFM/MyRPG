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
        inf->key_list[i] = my_strdup((char *)list[i], my_malloc);
}

void init_fps(wininf *inf)
{
    sfRenderWindow_setFramerateLimit(inf->win, inf->settings->c_fps < 5 ?
    my_atoi(inf->settings->fps[inf->settings->c_fps]) : 0);
    sfText_setString(
    ((choices *)inf->options_menu->choices->prev->prev->prev->data)->choice
    , inf->settings->fps[inf->settings->c_fps]);
    sfIntRect r; r.top = 0; r.left = 0;
    sfVector2f old_pos = sfSprite_getPosition(((choices *)inf->ig_options_menu
    ->choices->prev->prev->data)->choice);
    inf->ig_choices[2] = load_line(inf->settings->fps[inf->settings->c_fps],
    FONT_SIZE, inf, my_malloc);
    r.width = inf->ig_choices[2]->steps[inf->ig_choices[2]->max], r.height =
    inf->ig_choices[2]->height;
    sfSprite_setTextureRect(inf->ig_choices[2]->sps[0], r);
    sfSprite_destroy(((choices *)inf->ig_options_menu->choices->prev->prev
    ->data)->choice);
    ((choices *)inf->ig_options_menu->choices->prev->prev->data)->choice =
    inf->ig_choices[2]->sps[0];
    sfSprite_setPosition(((choices *)inf->ig_options_menu->choices->prev->prev
    ->data)->choice, old_pos);
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
    inf.state = create_shiny_test();
    inf.scenes[0] = create_home(&inf, inf.settings->house);
    inf.scenes[1] = create_static_env(&inf, 0);
    inf.scenes[3] = create_static_env(&inf, 6);
    inf.scenes[4] = create_static_env(&inf, 2);
    inf.scenes[5] = create_static_env(&inf, 4);
    inf.scenes[2] = create_static_env(&inf, 6 + inf.settings->house * 2);
    inf.camera = init_camera(inf);
    create_triggers(&inf);
    inf.transition = 0;
    inf.ftransi = 0.0f;
    inf.change_scene = 0;
    dungeon d; d.img = sfImage_createFromFile("result8.png"); d.in = 0;
    d.enemies = 0;
    inf.dungeon = d;
    inf.transi = my_rectangle();
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
    inf.change_keys_menu = init_all_menus(&inf, KEYBINDS_IDX, 0);                                                                                                                                                                                                         inf.options_menu = init_all_menus(&inf, OPTIONS_IDX, 0);
    inf.pause_menu = init_ig_menus(&inf, PAUSE_VILLAGE_IDX, 0);
    inf.others_menu = init_ig_menus(&inf, OTHERS_IDX, 0);
    inf.ig_options_menu = init_ig_menus(&inf, IG_OPTIONS_IDX, 0);
    init_options_pointers(&inf);
    inf.c_menu = NONE;
    inf.waiting_key = 0;
    inf.current_menu = inf.main_menu;
    inf.prev_menu = NULL;
    int tmp[2] = {100, 100};
    inf.volumes = my_malloc(sizeof(int) * 2);
    for (int i = 0; i < 2; i++) inf.volumes[i] = tmp[i];
    inf.net->timeout.microseconds = 5000;
    inf.intro = NULL; inf.ditto = NULL; inf.dream = NULL;
    inf.quiz = NULL;
    inf.playtime = load_line("VOID", FONT_SIZE, &inf, malloc);
    inf.ig_choices[0] = load_line("VOID", FONT_SIZE, &inf, malloc);
    inf.ig_choices[1] = load_line("VOID", FONT_SIZE, &inf, malloc);
    inf.ig_choices[2] = load_line("VOID", FONT_SIZE, &inf, malloc);
    inf.pressed = 0;
    init_fps(&inf);
    init_key_list(&inf); inf.key_change = -1; inf.play_time = my_clock();
    set_pokemon(&inf);
    return inf;
}
