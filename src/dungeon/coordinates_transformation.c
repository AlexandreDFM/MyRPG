/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** coordinates_transformation
*/

#include "rpg.h"

sfVector2f local_to_global(int x, int y)
{
    return (sfVector2f){x * 24.0f + 12.0f, y * 24.0f + 12.0f};
}

sfVector2i global_to_local(sfVector2f p) {
    int a = p.x / 24.0f;
    int b = p.y / 24.0f;
    return (sfVector2i){a, b};
}
