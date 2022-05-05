/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** network_syncing
*/

#include "rpg.h"

void send_sync(components *all)
{
    network *net = all->inf.net;
    sfPacket_clear(net->packet);
    my_printf(stderr, "Asked to sync...\n");
    sfPacket_clear(net->packet);
    int order = HSYNC;
    sfPacket_append(net->packet, &order, sizeof(int));
    sfVector2f pos = sfSprite_getPosition(all->pla->test);
    sfPacket_append(net->packet, &pos, sizeof(sfVector2f));
    int poke = all->inf.settings->pokemon;
    sfPacket_append(net->packet, &all->inf.c_scene, sizeof(int));
    sfPacket_append(net->packet, &poke, sizeof(int));
    sfUdpSocket_sendPacket(net->socket, net->packet, net->other.ip,
        net->other.port);
    sfPacket_clear(net->packet);
}

void sync_online(components *all)
{
    network *net = all->inf.net;
    int poke = all->inf.settings->pokemon;
    sfPacket_clear(net->packet);
    add_ord(CSYNC, &poke, sizeof(int), net->packet);
    net->flags[CSYNC] = 1;
}
