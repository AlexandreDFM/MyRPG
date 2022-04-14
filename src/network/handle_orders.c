/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** handle_orders
*/

#include "rpg.h"

int receive_okay(char **data, int *important, components *all)
{
    network *net = all->inf.net;
    int ord_to_remove = *((int*)*data);
    *data += sizeof(int);
    net->flags[ord_to_remove] = 0;
    my_printf("RECEIVED OKAY\n");
    return sizeof(int);
}

int receive_hostsync(char **data, int *important, components *all)
{
    my_printf("RECEIVED HostSync: %d\n", *((int*)(*data)));
    return sizeof(int);
}

int receive_clientsync(char **data, int *important, components *all)
{
    printf("Pokemon: %d\n", *((int*)*data));
    *data += sizeof(int);
    int ans = CSYNC;
    add_ord(OKAY, &ans, sizeof(int), all->inf.net->packet);
    return sizeof(int) * 2;
}

int receive_connection(char **data, int *important, components *all)
{
    my_printf("RECEIVED CONNECTION\n");
    *important = 1;
    sfIpAddress *client_ip = (sfIpAddress*)(*data);
    *data += sizeof(sfIpAddress);
    int *port = (int*) *data;
    all->inf.net->other.ip = *client_ip;
    all->inf.net->other.port = *port;
    return sizeof(int) * 2 + sizeof(sfIpAddress);
}

int receive_position(char **data, int *important, components *all)
{
    my_printf("RECEIVED POSITION\n");
    *data += sizeof(sfVector2f);
    return sizeof(int) + sizeof(sfVector2f);
}

int receive_scene(char **data, int *important, components *all)
{
    my_printf("RECIEVED SCENE\n");
    *important = 1;
    *data += sizeof(int);
    return sizeof(int) * 2;
}
