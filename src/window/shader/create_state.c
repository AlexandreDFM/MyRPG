/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_state
*/

#include "rpg.h"

sfRenderStates create_shiny_test(void)
{
    sfRenderStates state;
    state.blendMode = sfBlendAlpha;
    state.shader = sfShader_createFromFile(0, 0,
        "src/window/shader/shiny.glsl");
    state.transform = sfTransform_Identity;
    state.texture = 0;
    return state;
}
