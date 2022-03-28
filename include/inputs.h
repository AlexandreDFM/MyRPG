/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** inputs
*/

#ifndef INPUTS_H_
#define INPUTS_H_

    #include "infos.h"

typedef enum input_types_t {
    KEYBOARD,
    CONTROLLER,
} input_types;

typedef struct keybinds_t {
    sfKeyCode left;
    sfKeyCode right;
    sfKeyCode up;
    sfKeyCode down;
    sfKeyCode interact;
} keybinds;

typedef struct inputs_t {
    sfVector2f axis;
    int interact;
    enum input_types_t type;
    struct keybinds_t *keys;
} inputs;

void init_inputs(wininf *inf);
void update_inputs(wininf *inf);
void update_keyboard(wininf *inf);
void update_joysticks(wininf *inf);

#endif /* !INPUTS_H_ */
