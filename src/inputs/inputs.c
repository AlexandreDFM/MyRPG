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
    in.keys.up = sfKeyZ;
    in.keys.down = sfKeyS;
    in.keys.left = sfKeyQ;
    in.keys.right = sfKeyD;
    in.keys.interact = sfKeyE;
    in.keys.inventory = sfKeyI;
    in.keys.attack = sfKeySpace;
    in.keys.back = sfKeyEscape;
    in.keys.mup = sfKeyUp;
    in.keys.mdown = sfKeyDown;
    in.keys.mleft = sfKeyLeft;
    in.keys.mright = sfKeyRight;
    in.axis = (sfVector2f){0.0f, 0.0f};
    in.interact = 0;
    in.can_interact = 0;
    in.interact_callback = -1;
    inf->inputs = in;
}

sfKeyCode check_key_valid(wininf *inf)
{
    if (inf->inputs.keys.up == inf->tmp_key) return -1;
    if (inf->inputs.keys.down == inf->tmp_key) return -1;
    if (inf->inputs.keys.left == inf->tmp_key) return -1;
    if (inf->inputs.keys.right == inf->tmp_key) return -1;
    if (inf->inputs.keys.interact == inf->tmp_key) return -1;
    if (inf->inputs.keys.inventory == inf->tmp_key) return -1;
    if (inf->inputs.keys.attack == inf->tmp_key) return -1;
    if (inf->inputs.keys.back == inf->tmp_key) return -1;
    return inf->tmp_key;
}

void update_temporary_key(wininf *inf)
{
    if (inf->key_change == 0) inf->inputs.keys.up = inf->tmp_key;
    if (inf->key_change == 1) inf->inputs.keys.down = inf->tmp_key;
    if (inf->key_change == 2) inf->inputs.keys.left = inf->tmp_key;
    if (inf->key_change == 3) inf->inputs.keys.right = inf->tmp_key;
    if (inf->key_change == 4) inf->inputs.keys.interact = inf->tmp_key;
    if (inf->key_change == 5) inf->inputs.keys.inventory = inf->tmp_key;
    if (inf->key_change == 6) inf->inputs.keys.attack = inf->tmp_key;
    if (inf->key_change == 7) inf->inputs.keys.back = inf->tmp_key;
    if (inf->key_change == 8) inf->inputs.keys.mup = inf->tmp_key;
    if (inf->key_change == 9) inf->inputs.keys.mdown = inf->tmp_key;
    if (inf->key_change == 10) inf->inputs.keys.mleft = inf->tmp_key;
    if (inf->key_change == 11) inf->inputs.keys.mright = inf->tmp_key;
}

void update_key(wininf *inf)
{
    if (check_key_valid(inf) >= 0)
        update_temporary_key(inf);
    inf->waiting_key = 38;
    inf->key_change = -1;
    sfText *tmp_t = ((choices *)inf->current_menu->selected->data)->choice;
    sfVector2f pos = sfText_getPosition(tmp_t);
    pos.y -= 20;
    sfText_setPosition(tmp_t, pos);
    sfText_setString(tmp_t, inf->tmp_key >= 0 ?
    inf->key_list[inf->tmp_key] : "Unknown key");

}

void update_inputs(wininf *inf)
{
    if (inf->waiting_key == 37) {
        update_key(inf);
        return;
    }
    inf->inputs.axis.x = 0.0f; inf->inputs.axis.y = 0.0f;
    int old_interact = inf->inputs.interact, old_attack = inf->inputs.attack;
    int old_back = inf->inputs.back, old_pause = inf->inputs.pause;
    inf->inputs.interact = 0;
    inf->inputs.attack = 0;
    inf->inputs.back = 0;
    sfJoystick_update();
    if (sfJoystick_isConnected(0)) {
        inf->inputs.type = CONTROLLER;
        update_joysticks(inf);
    }
    inf->inputs.type = KEYBOARD;
    update_keyboard(inf); treat_axis(inf);
    if (old_interact != inf->inputs.interact && old_interact)
        inf->inputs.can_interact = 0;
    if (old_attack != inf->inputs.attack && old_attack)
        inf->inputs.can_attack = 0;
    if (old_back != inf->inputs.back && old_back)
        inf->inputs.can_back = 1;
    if (old_pause != inf->inputs.pause && old_pause)
        inf->inputs.can_pause = 1;
    if (inf->interacting) inf->inputs.axis = (sfVector2f){0.0f, 0.0f};
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
    i->inputs.axis.y -= (float)sfKeyboard_isKeyPressed(i->inputs.keys.mup);
    i->inputs.axis.y += (float)sfKeyboard_isKeyPressed(i->inputs.keys.mdown);
    i->inputs.axis.x -= (float)sfKeyboard_isKeyPressed(i->inputs.keys.mleft);
    i->inputs.axis.x += (float)sfKeyboard_isKeyPressed(i->inputs.keys.mright);
    int inter = (int)sfKeyboard_isKeyPressed(i->inputs.keys.interact);
    int attack = (int)sfKeyboard_isKeyPressed(i->inputs.keys.attack);
    i->inputs.attack = attack, i->inputs.interact += inter;
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
        inf->inputs.back += sfJoystick_isButtonPressed(0, 1);
        inf->inputs.back += sfJoystick_isButtonPressed(0, 7);
    }
    x = fabs(x) > 0.35f ? x : 0.0f;
    y = fabs(y) > 0.35f ? y : 0.0f;
    inf->inputs.axis = (sfVector2f){x, y};
}
