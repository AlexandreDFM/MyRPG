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
    my_printf("Asked to sync...\n");
    sfPacket_clear(net->packet);
    int order = SYNC;
    sfPacket_append(net->packet, &order, sizeof(int));
    sfVector2f pos = sfSprite_getPosition(all->pla.test);
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
    int order = SYNC;
    network *net = all->inf.net;
    sfPacket_clear(net->packet);
    sfPacket_append(net->packet, &order, sizeof(int));
    int poke = all->inf.settings->pokemon;
    sfPacket_append(net->packet, &poke, sizeof(int));
    my_printf("Waiting to sync...\n");
    net->is_okay = 0;
    while (!net->is_okay) {
        sfUdpSocket_sendPacket(net->socket, net->packet, net->other.ip, net->other.port);
        if (sfSocketSelector_wait(net->selector, net->timeout)) {
            if (!sfSocketSelector_isUdpSocketReady(net->selector, net->socket))
                continue;
            int res = sfUdpSocket_receivePacket(net->socket, net->packet, &net->other.ip, &net->other.port);
            if (!res) {
                void *data = sfPacket_getData(net->packet);
                int *order = data;
                data += sizeof(int);
                if (*order == SYNC) {
                    sfVector2f *np = data;
                    data += sizeof(sfVector2f);
                    int *scene = data;
                    data += sizeof(int);
                    sfSprite_setPosition(all->pla.test, *np);
                    int *poke = data;
                    net->other.p = init_player(all->inf, *poke);
                    sfSprite_setPosition(net->other.p.test, *np);
                    net->other.target = *np;
                    all->inf.c_scene = *scene;
                    net->other.cscene = *scene;
                    net->is_okay = 1;
                }
            }
        }
    }
    sfPacket_clear(net->packet);
    my_printf("Synced !\n");
}
