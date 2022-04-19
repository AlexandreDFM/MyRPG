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
    sfUdpSocket_sendPacket(net->socket, net->packet, net->other.ip,
        net->other.port);
    sfIpAddress *ip = &(net->other.ip);
    sfPacket_clear(p);
    if (sfSocketSelector_wait(net->selector, net->timeout)) {
        if (sfSocketSelector_isUdpSocketReady(net->selector, net->socket)) {
            sfUdpSocket_receivePacket(net->socket, p, ip, &net->port);
            receive_ord(net, all);
        }
    }
}

void receive_ord(network *net, components *all)
{
    int important = 0;
    int scanned = 0;
    int total = sfPacket_getDataSize(net->packet);
    const void *data = sfPacket_getData(net->packet);
    char *castdata = (void *) data;
    if (total < sizeof(int)) return;
    while (scanned < total) {
        int *ord = (int*) castdata;
        my_printf("Order received: %d (%dbytes)\n", *ord, total);
        castdata += sizeof(int);
        scanned += sizeof(int);
        if (net->orders[*ord])
            scanned += net->orders[*ord]((char**)&castdata, &important, all);
        else
            my_printf("Order not implemented ! (%d)\n", *ord);
    }
    sfPacket_clear(net->packet);
}

void add_ord(int ord, void *data, int size, sfPacket *packet)
{
    if (ord != -1) {
        sfPacket_append(packet, &ord, sizeof(int));
    }
    if (data) {
        sfPacket_append(packet, data, size);
    }
}
