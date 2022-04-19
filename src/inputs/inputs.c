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
    inputs in;
    in.keys.down = sfKeyS;
    in.keys.up = sfKeyZ;
    in.keys.left = sfKeyQ;
    in.keys.right = sfKeyD;
    in.keys.interact = sfKeyE;
    in.axis = (sfVector2f){0.0f, 0.0f};
    in.interact = 0;
    in.can_interact = 0;
    in.interact_callback = -1;
    inf->inputs = in;
}

void update_inputs(wininf *inf)
{
    inf->inputs.axis.x = 0.0f;
    inf->inputs.axis.y = 0.0f;
    int old_interact = inf->inputs.interact;
    inf->inputs.interact = 0;
    sfJoystick_update();
    if (sfJoystick_isConnected(0)) {
        inf->inputs.type = CONTROLLER;
        update_joysticks(inf);
    }
    inf->inputs.type = KEYBOARD;
    update_keyboard(inf);
    treat_axis(inf);
    if (old_interact != inf->inputs.interact && old_interact)
        inf->inputs.can_interact = 0;
    if (inf->interacting) {
        inf->inputs.axis = (sfVector2f){0.0f, 0.0f};
    }
}

void treat_axis(wininf *inf)
{
    if (inf->inputs.axis.x > 0.1f) inf->inputs.axis.x = 1.0f;
    if (inf->inputs.axis.x < -0.1f) inf->inputs.axis.x = -1.0f;
    if (inf->inputs.axis.y > 0.1f) inf->inputs.axis.y = 1.0f;
    if (inf->inputs.axis.y < -0.1f) inf->inputs.axis.y = -1.0f;
    inf->inputs.axis.x = my_clamp(inf->inputs.axis.x, -1.0f, 1.0f);
    inf->inputs.axis.y = my_clamp(inf->inputs.axis.y, -1.0f, 1.0f);
}

void update_keyboard(wininf *i)
{
    i->inputs.axis.y -= (float)sfKeyboard_isKeyPressed(i->inputs.keys.up);
    i->inputs.axis.y += (float)sfKeyboard_isKeyPressed(i->inputs.keys.down);
    i->inputs.axis.x -= (float)sfKeyboard_isKeyPressed(i->inputs.keys.left);
    i->inputs.axis.x += (float)sfKeyboard_isKeyPressed(i->inputs.keys.right);
    int inter = (int)sfKeyboard_isKeyPressed(i->inputs.keys.interact);
    i->inputs.interact += inter;
}

void update_joysticks(wininf *inf)
{
    int has_2d = sfJoystick_hasAxis(0, sfJoystickX);
    has_2d = has_2d && sfJoystick_hasAxis(0, sfJoystickY);
    float x = 0.0f;
    float y = 0.0f;
    if (has_2d) {
        x = sfJoystick_getAxisPosition(0, sfJoystickX) / 100.0f;
        y = sfJoystick_getAxisPosition(0, sfJoystickY) / 100.0f;
    }
    if (sfJoystick_getButtonCount(0)) {
        inf->inputs.interact += sfJoystick_isButtonPressed(0, 2);
    }
    x = fabs(x) > 0.35f ? x : 0.0f;
    y = fabs(y) > 0.35f ? y : 0.0f;
    inf->inputs.axis = (sfVector2f){x, y};
}
