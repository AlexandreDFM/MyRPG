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
    if (sfSocketSelector_wait(net->selector, net->timeout)) {
        if (sfSocketSelector_isUdpSocketReady(net->selector, net->socket)) {
            sfUdpSocket_receivePacket(net->socket, p, net->ip, &net->port);
            receive_ord(net, all);
        }
    }
    sfPacket_clear(p);
}

void receive_ord(network *net, components *all)
{
    int important = 0;
    int scanned = 0;
    int total = sfPacket_getDataSize(net->packet);
    void *data = sfPacket_getData(net->packet);
    if (total < sizeof(int)) return;
    while (scanned < total) {
        int *ord = data;
        my_printf("Order received: %d\n", *ord);
        data += sizeof(int);
        scanned += sizeof(int);
        if (net->orders[*ord])
            scanned += net->orders[*ord](&data, &important, all);
        else
            my_printf("Order not implemented ! (%d)\n", *ord);
        // printf("Scanned: %d == %d\n", scanned, total);
    }
    sfPacket_clear(net->packet);
    // if (important) {
    //     add_ord(OKAY, 0, 0, net->packet);
    // }
}

void add_ord(int ord, void *data, int size, sfPacket *packet)
{
    sfPacket_append(packet, &ord, sizeof(int));
    if (data) {
        sfPacket_append(packet, &data, size);
    }
}

void handle_packet(components *all, void *data)
{
    network *net = all->inf.net;
    if (!data) return;
    int *order = data;
    data += sizeof(int);
    if (*order == CONNECTION) {
        printf("Received connection: %d\n", *order);
        sfIpAddress *client_ip = (sfIpAddress*)data;
        data += sizeof(sfIpAddress);
        int *port = data;
        net->other.ip = *client_ip;
        net->other.port = *port;
        send_okay(net);
    }
    if (*order == SYNC) {
        if (!all->inf.net->is_host) return;
        int *id = data;
        int poke = *id;
        send_sync(all);
        if (net->other.p.test) return;
        net->other.p = init_player(all->inf, poke);
        sfVector2f np = sfSprite_getPosition(all->pla.test);
        net->other.target = np;
        net->other.cscene = all->inf.c_scene;
        sfSprite_setPosition(net->other.p.test, np);
    }
    if (*order == OKAY) {
        net->is_okay = 1;
    }
    // if (*order == CHANGE_SCENE) {
    //     int *id = data;
    //     data += sizeof(int);
    //     if (*id != net->is_host) {
    //         int *nscene = data;
    //         net->other.cscene = *nscene;
    //         send_okay(net);
    //     }
    // }
    if (*order == POSITION) {
        int *id = data;
        data += sizeof(int);
        if (*id != net->is_host) {
            sfVector2f *np = data;
            sfVector2f pos = *np;
            net->other.target = pos;
        }
    }
}
