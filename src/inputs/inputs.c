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
    in.keys.up = sfKeyZ; in.keys.down = sfKeyS;
    in.keys.left = sfKeyQ; in.keys.right = sfKeyD;
    in.keys.interact = sfKeyE; in.keys.inventory = sfKeyI;
    in.keys.attack = sfKeySpace; in.keys.back = sfKeyEscape;
    in.keys.mup = sfKeyUp; in.keys.mdown = sfKeyDown;
    in.keys.mleft = sfKeyLeft;
    in.keys.mright = sfKeyRight;
    in.axis = (sfVector2f){0.0f, 0.0f};
    in.interact = 0; in.back = 0; in.pause = 0; in.attack = 0;
    in.can_interact = 0; in.can_attack = 1; in.can_back = 1; in.can_pause = 1;
    in.interact_callback = -1;
    inf->inputs = in;
}

void update_olds(sfIntRect r, wininf *inf)
{
    if (r.left != inf->inputs.interact && r.left)
        inf->inputs.can_interact = 0;
    if (r.top != inf->inputs.attack && r.top)
        inf->inputs.can_attack = 1;
    if (r.width != inf->inputs.back && r.width)
        inf->inputs.can_back = 1;
    if (r.height != inf->inputs.pause && r.height)
        inf->inputs.can_pause = 1;
    if (inf->interacting) inf->inputs.axis = (sfVector2f){0.0f, 0.0f};
}

void update_inputs(wininf *inf)
{
    if (inf->waiting_key == 37) {
        update_key(inf);
        return;
    }
    inf->inputs.axis.x = 0.0f; inf->inputs.axis.y = 0.0f;
    int o_int = inf->inputs.interact, old_attack = inf->inputs.attack;
    int old_back = inf->inputs.back, old_pause = inf->inputs.pause;
    inf->inputs.interact = 0; inf->inputs.attack = 0;
    inf->inputs.back = 0; inf->inputs.pause = 0;
    sfJoystick_update();
    if (sfJoystick_isConnected(0)) {
        inf->inputs.type = CONTROLLER;
        update_joysticks(inf);
    }
    inf->inputs.type = KEYBOARD;
    update_keyboard(inf); treat_axis(inf);
    update_olds((sfIntRect){o_int, old_attack, old_back, old_pause}, inf);
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
