/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** handle_orders
*/

#include "rpg.h"

int receive_okay(void **data, int *important, components *all)
{
    my_printf("RECEIVED OKAY\n");
    return sizeof(int);
}

int receive_position(void **data, int *important, components *all)
{
    my_printf("RECEIVED POSITION\n");
    *data += sizeof(sfVector2f);
    return sizeof(int) + sizeof(sfVector2f);
}

int receive_scene(void **data, int *important, components *all)
{
    my_printf("RECIEVED SCENE\n");
    *important = 1;
    *data += sizeof(int);
    return sizeof(int) * 2;
}
