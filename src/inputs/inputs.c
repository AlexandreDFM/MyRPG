/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** inputs
*/

#include "infos.h"
#include "inputs.h"

void init_inputs(wininf *inf)
{
    inputs *in = malloc(sizeof(inputs));
    in->keys = malloc(sizeof(keybinds));
    in->keys->down = sfKeyS;
    in->keys->up = sfKeyZ;
    in->keys->left = sfKeyQ;
    in->keys->right = sfKeyD;
    in->keys->interact = sfKeyE;
    inf->inputs = in;
}

void update_inputs(wininf *inf)
{
    inf->inputs->axis.x = 0.0f; inf->inputs->axis.y = 0.0f;
    sfJoystick_update();
    if (sfJoystick_isConnected(0)) {
        inf->inputs->type = CONTROLLER;
        update_joysticks(inf);
        return;
    }
    inf->inputs->type = KEYBOARD;
    update_keyboard(inf);
}

void update_keyboard(wininf *inf)
{
    inputs *in = inf->inputs;
    in->axis.y -= (float)sfKeyboard_isKeyPressed(in->keys->up);
    in->axis.y += (float)sfKeyboard_isKeyPressed(in->keys->down);
    in->axis.x -= (float)sfKeyboard_isKeyPressed(in->keys->left);
    in->axis.x += (float)sfKeyboard_isKeyPressed(in->keys->right);
    in->interact = (int)sfKeyboard_isKeyPressed(in->keys->interact);
}

void update_joysticks(wininf *inf)
{
    int has_2d = sfJoystick_hasAxis(0, sfJoystickX);
    has_2d = has_2d && sfJoystick_hasAxis(0, sfJoystickY);
    if (has_2d) {
        float x = sfJoystick_getAxisPosition(0, sfJoystickX) / 100.0f;
        float y = sfJoystick_getAxisPosition(0, sfJoystickY) / 100.0f;
        inf->inputs->axis = (sfVector2f){x, y};
    }
    if (sfJoystick_getButtonCount(0)) {
        inf->inputs->interact = sfJoystick_isButtonPressed(0, 0);
    }
}