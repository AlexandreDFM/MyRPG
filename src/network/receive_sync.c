/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** receive_sync
*/

#include "rpg.h"

int receive_okay(char **data, int *important, components *all)
{
    network *net = all->inf.net;
    int ord_to_remove = *((int *)*data);
    *data += sizeof(int);
    net->flags[ord_to_remove] = 0;
    return sizeof(int);
}

int receive_hostsync(char **data, int *important, components *all)
{
    network *net = all->inf.net;
    net->other.p = init_player(all->inf, *((int *)*data));
    *data += sizeof(int);
    sfVector2f pos = *((sfVector2f*)*data);
    sfSprite_setPosition(net->other.p->test, pos);
    net->other.target = pos;
    *data += sizeof(sfVector2f);
    net->other.cscene = *((int *)*data);
    all->inf.c_scene = net->other.cscene;
    *data += sizeof(int);
    return sizeof(int) * 3 + sizeof(sfVector2f);
}

int receive_clientsync(char **data, int *important, components *all)
{
    network *net = all->inf.net;
    all->inf.net->other.cscene = all->inf.c_scene;
    all->inf.net->other.p = init_player(all->inf, *((int *)*data));
    sfVector2f pos = sfSprite_getPosition(all->pla->test);
    all->inf.net->other.target = pos;
    sfSprite_setPosition(all->inf.net->other.p->test, pos);
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
