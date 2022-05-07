/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** update_inputs
*/

#include "rpg.h"

void update_keyboard(wininf *i)
{
    i->inputs.axis.y -= (float)sfKeyboard_isKeyPressed(i->inputs.keys.up);
    i->inputs.axis.y += (float)sfKeyboard_isKeyPressed(i->inputs.keys.down);
    i->inputs.axis.x -= (float)sfKeyboard_isKeyPressed(i->inputs.keys.left);
    i->inputs.axis.x += (float)sfKeyboard_isKeyPressed(i->inputs.keys.right);
    i->inputs.axis.y -= (float)sfKeyboard_isKeyPressed(i->inputs.keys.mup);
    i->inputs.axis.y += (float)sfKeyboard_isKeyPressed(i->inputs.keys.mdown);
    i->inputs.axis.x -= (float)sfKeyboard_isKeyPressed(i->inputs.keys.mleft);
    i->inputs.axis.x += (float)sfKeyboard_isKeyPressed(i->inputs.keys.mright);
    int inter = (int)sfKeyboard_isKeyPressed(i->inputs.keys.interact);
    int attack = (int)sfKeyboard_isKeyPressed(i->inputs.keys.attack);
    i->inputs.attack += attack, i->inputs.interact += inter;
    i->inputs.back += (int)sfKeyboard_isKeyPressed(i->inputs.keys.back);
    i->inputs.pause += (int)sfKeyboard_isKeyPressed(i->inputs.keys.back);
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
        x += sfJoystick_getAxisPosition(0, sfJoystickPovX) / 100.0f;
        y += sfJoystick_getAxisPosition(0, sfJoystickPovY) / 100.0f;
    }
    if (sfJoystick_getButtonCount(0)) {
        inf->inputs.interact += sfJoystick_isButtonPressed(0, 2);
        inf->inputs.attack += sfJoystick_isButtonPressed(0, 0);
        inf->inputs.pause += sfJoystick_isButtonPressed(0, 1);
        inf->inputs.back += sfJoystick_isButtonPressed(0, 7);
    }
    x = fabs(x) > 0.35f ? x : 0.0f; y = fabs(y) > 0.35f ? y : 0.0f;
    inf->inputs.axis = (sfVector2f){x, y};
}
