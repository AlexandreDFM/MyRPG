/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** manage_intro
*/

#include "rpg.h"
#include "intro.h"

void manage_intro(wininf *inf)
{
    if (inf->intro == NULL) return;
    if (inf->intro->valid == 0 && inf->c_scene == INTRO && inf->intro->plan != PLAN6) {
        if (inf->event.type == sfEvtKeyPressed || (inf->event.mouseButton.type == sfEvtMouseButtonPressed && inf->event.mouseButton.button != sfMouseRight)) {
            sfMusic_pause(inf->intro->i_music1);
            sfMusic_play(inf->intro->i_music2);
            inf->intro->i_music1;
            inf->intro->b_intro[0].rect = (sfIntRect) {4456 + 480, 608, 240, 160};
            inf->intro->b_intro[1].rect = (sfIntRect) {4456 + 480, 448, 240, 160};
            inf->intro->b_intro[2].rect = (sfIntRect) {4456 + 720, 481, 96, 29};
            inf->intro->b_intro[2].pos = (sfVector2f) {4456 + 120 + 75 * 7, 118 * 7};
            inf->intro->b_intro[3].rect = (sfIntRect) {4456 + 1011, 483, 96, 29};
            inf->intro->b_intro[3].pos = (sfVector2f) {4456 + 120 + 75 * 7, (118 + 28) * 7};
            inf->time.intro_anim = 0.0f;
            inf->intro->valid += 1;
            inf->intro->plan = PLAN6;
        }
    }
    if (inf->intro->valid == 1 && (inf->event.type == sfEvtKeyReleased || (inf->event.mouseButton.type == sfEvtMouseButtonReleased && inf->event.mouseButton.button != sfMouseRight))) {
        inf->intro->valid += 1;
    }
    if (inf->intro->valid != 0 && inf->c_scene == INTRO && inf->intro->plan == PLAN6) {
        if (inf->intro->valid >= 2 && (inf->event.type == sfEvtKeyPressed || (inf->event.mouseButton.type == sfEvtMouseButtonPressed && inf->event.mouseButton.button != sfMouseRight))) {
            inf->intro->plan = DELETEINTRO;
        }
    }
}
