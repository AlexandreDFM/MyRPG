/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** connecting_utils
*/

#include "rpg.h"

void try_to_connect(sfIpAddress ip, int port, wininf *inf)
{
    int iter = 0;
    network *net = inf->net;
    sfIpAddress my_ip = sfIpAddress_getLocalAddress();
    sfUdpSocket_bind(net->socket, port, my_ip);
    sfIpAddress *addrip = &my_ip;
    int *addrport = &port;
    int order = CONNECTION;
    sfSocketSelector_addUdpSocket(inf->net->selector, inf->net->socket);
    while (iter <= 30) {
        sfPacket_clear(net->packet);
        sfPacket_append(net->packet, &order, sizeof(int));
        sfPacket_append(net->packet, addrip, sizeof(sfIpAddress));
        sfPacket_append(net->packet, addrport, sizeof(int));
        sfUdpSocket_sendPacket(net->socket, net->packet, ip, port);
        if (receive_with_timeout(net, addrip, (short unsigned int *)addrport))
            break;
        iter += 1;
    }
}

int receive_with_timeout(network *net, sfIpAddress *ip, short unsigned int *p)
{
    if (sfSocketSelector_wait(net->selector, net->timeout)) {
        if (!sfSocketSelector_isUdpSocketReady(net->selector, net->socket))
            return 0;
        int res = sfUdpSocket_receivePacket(net->socket, net->packet, ip, p);
        if (!res) {
            net->other.ip = *ip;
            net->other.port = *p;
            net->other.connected = 1;
            my_printf(stdout, "Successfully connected!\n");
            return 1;
        }
    }
    return 0;
}

network *init_network(void)
{
    network *net = my_malloc(sizeof(network));
    net->is_host = 0;
    net->is_multi = 0;
    net->packet = 0;
    net->socket = 0;
    init_orders(net);
    net->other.ip = sfIpAddress_None;
    net->other.port = 0;
    net->other.connected = 0;
    net->is_okay = 1;
    net->selector = my_sock_select();
    sfTime timeout;
    timeout.microseconds = 1000000;
    net->timeout = timeout;
    net->other.cscene = -1;
    return net;
}

void init_orders(network *net)
{
    net->orders[OKAY] = receive_okay;
    net->orders[CONNECTION] = receive_connection;
    net->orders[CSYNC] = receive_clientsync;
    net->orders[HSYNC] = receive_hostsync;
    net->orders[POSITION] = receive_position;
    net->orders[CHANGE_SCENE] = receive_scene;
    net->orders[SETPOS] = receive_setposition;
    net->orders[DUNGEONSYNC] = receive_dungeon_info;
}
