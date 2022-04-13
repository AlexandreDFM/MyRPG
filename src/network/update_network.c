/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** update_network
*/

#include "rpg.h"

void update_network(wininf *inf, components *all)
{
    network *net = inf->net;
    if (!inf->net->is_multi) return;
    sfPacket *p = inf->net->packet;
    sfPacket_clear(p);
    int res = sfUdpSocket_receivePacket(net->socket, p, net->ip, &net->port);
    if (res == sfSocketDone) {
        void *data = sfPacket_getData(p);
        handle_packet(all, data);
    }
}

void send_sync(components *all)
{
    network *net = all->inf.net;
    my_printf("Asked to sync...\n");
    sfPacket_clear(net->packet);
    int order = SYNC;
    sfPacket_append(net->packet, &order, sizeof(int));
    sfVector2f pos = sfSprite_getPosition(all->pla.test);
    sfPacket_append(net->packet, &pos, sizeof(sfVector2f));
    int poke = all->inf.settings->pokemon;
    sfPacket_append(net->packet, &all->inf.c_scene, sizeof(int));
    sfPacket_append(net->packet, &poke, sizeof(int));
    sfUdpSocket_sendPacket(net->socket, net->packet, net->other.ip, net->other.port);
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
                    all->inf.c_scene = *scene;
                    net->is_okay = 1;
                }
            }
        }
        sfPacket_clear(net->packet);
    }
    my_printf("Synced !\n");
}

void handle_packet(components *all, void *data)
{
    network *net = all->inf.net;
    int *order = data;
    data += sizeof(int);
    if (*order == CONNECTION) {
        printf("Recieved connection: %d\n", *order);
        sfIpAddress *client_ip = (sfIpAddress*)data;
        data += sizeof(sfIpAddress);
        int *port = data;
        net->other.ip = *client_ip;
        net->other.port = *port;
        send_okay(net);
    }
    if (*order == SYNC) {
        send_sync(all);
        data += sizeof(int);
        int *id = data;
        net->other.p = init_player(all->inf, *id);
    }
    if (*order == OKAY) {
        net->is_okay = 1;
    }
}
