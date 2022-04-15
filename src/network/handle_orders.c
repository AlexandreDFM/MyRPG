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
    network *net = all->inf.net;
    net->other.p = init_player(all->inf, *((int*)*data));
    *data += sizeof(int) * 2 + sizeof(sfVector2f);
    return sizeof(int) * 3 + sizeof(sfVector2f);
}

int receive_clientsync(char **data, int *important, components *all)
{
    network *net = all->inf.net;
    all->inf.net->other.cscene = all->inf.c_scene;
    all->inf.net->other.p = init_player(all->inf, *((int*)*data));
    sfVector2f pos = sfSprite_getPosition(all->pla.test);
    all->inf.net->other.target = pos;
    sfSprite_setPosition(all->inf.net->other.p.test, pos);
    *data += sizeof(int);
    int ans = CSYNC;
    sfPacket_clear(net->packet);
    settings *set = all->inf.settings;
    int scene = all->inf.c_scene;
    add_ord(OKAY, &ans, sizeof(int), all->inf.net->packet);
    add_ord(HSYNC, &set->pokemon, sizeof(int), all->inf.net->packet);
    add_ord(APPEND, &pos, sizeof(sfVector2f), all->inf.net->packet);
    add_ord(APPEND, &scene, sizeof(int), all->inf.net->packet);
    sfUdpSocket_sendPacket(net->socket, net->packet, net->other.ip,
        net->other.port);
    sfPacket_clear(net->packet);
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
