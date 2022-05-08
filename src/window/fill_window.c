/*
** EPITECH PROJECT, 2022
** main
** File description:
** Init of window
*/

#include "infos.h"
#include "music.h"
#include "inputs.h"
#include "sounds.h"
#include "rpg.h"

void first_fill_window(wininf *inf)
{
    inf->c_scene = INTRO;
    inf->interacting = 0;
    init_times(inf);
    create_atlases(inf);
    init_inputs(inf);
    inf->logs = 0;
    inf->log_path = "logs01"; inf->log_file = fopen(inf->log_path, "w+");
    inf->state = create_shiny_test();
    inf->scenes[0] = create_home(inf, inf->settings->house);
    inf->scenes[1] = create_static_env(inf, 0);
    inf->scenes[3] = create_static_env(inf, 6);
    inf->scenes[4] = create_static_env(inf, 2);
    inf->scenes[5] = create_static_env(inf, 4);
    inf->scenes[2] = create_static_env(inf, 6 + inf->settings->house * 2);
    inf->scenes[6] = create_static_env(inf, 50);
    inf->camera = init_camera(*inf);
    create_triggers(inf);
    inf->transition = 0;
    inf->ftransi = 0.0f;
}

void last_fill_window(wininf *inf)
{
    inf->intro = NULL; inf->ditto = NULL; inf->dream = NULL;
    inf->quiz = NULL;
    inf->playtime = load_line("VOID", FONT_SIZE, inf, malloc);
    inf->ig_choices[0] = load_line("VOID", FONT_SIZE, inf, malloc);
    inf->ig_choices[1] = load_line("VOID", FONT_SIZE, inf, malloc);
    inf->ig_choices[2] = load_line("VOID", FONT_SIZE, inf, malloc);
    inf->pressed = 0;
    inf->pause = 0;
    init_fps(inf);
    init_key_list(inf); inf->key_change = -1; inf->play_time = my_clock();
    set_pokemon(inf);
    inf->logs_textbox = generate_textbox((sfVector2i){205, 40},
        inf->atlases.atlas);
    sfSprite_setOrigin(inf->logs_textbox, (sfVector2f){100.0f, -25.0f});
    init_inventory(inf, 10);
    inf->sounds = init_sounds(); inf->music = init_musics();
    set_backs_menu(inf);
    inf->d_items = 0;
    inf->quest = 0;
}

void mid_fill_window(wininf *inf)
{
    init_main_menu_pointers(inf);
    inf->load_menu = init_all_menus(inf, LOAD_IDX, 0);
    init_load_pointers(inf);
    inf->options_menu = init_all_menus(inf, OPTIONS_IDX, 0);
    inf->change_keys_menu = init_all_menus(inf, KEYBINDS_IDX, 0);
    inf->pause_menu = init_ig_menus(inf, PAUSE_VILLAGE_IDX, 0);
    inf->others_menu = init_ig_menus(inf, OTHERS_IDX, 0);
    inf->ig_options_menu = init_ig_menus(inf, IG_OPTIONS_IDX, 0);
    inf->inventory_menu = init_ig_menus(inf, INVENTORY_IDX, 0);
    inf->use_item_menu = init_ig_menus(inf, USE_ITEM_IDX, 0);
    init_options_pointers(inf);
    inf->c_menu = NONE;
    inf->waiting_key = 0;
    inf->current_menu = inf->main_menu;
    inf->prev_menu = NULL;
    int tmp[2] = {100, 100};
    inf->volumes = my_malloc(sizeof(int) * 2);
    for (int i = 0; i < 2; i++) inf->volumes[i] = tmp[i];
    inf->net->timeout.microseconds = 5000;
}
