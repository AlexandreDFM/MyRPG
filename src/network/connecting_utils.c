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
    sfIpAddress *otherip = &ip;
    int *addrport = &port;
    int order = CONNECTION;
    sfSocketSelector_addUdpSocket(inf->net->selector, inf->net->socket);
    while (iter <= 30) {
        sfPacket_clear(net->packet);
        sfPacket_append(net->packet, &order, sizeof(int));
        sfPacket_append(net->packet, addrip, sizeof(sfIpAddress));
        sfPacket_append(net->packet, addrport, sizeof(int));
        sfUdpSocket_sendPacket(net->socket, net->packet, ip, port);
        if (receive_with_timeout(net, addrip, addrport))
            break;
        iter += 1;
    }
    net->other.ip = ip;
    net->other.port = port;
}

int receive_with_timeout(network *net, sfIpAddress *ip, int *port)
{
    if (sfSocketSelector_wait(net->selector, net->timeout)) {
        if (!sfSocketSelector_isUdpSocketReady(net->selector, net->socket))
            return 0;
        int res = sfUdpSocket_receivePacket(net->socket, net->packet, ip, port);
        if (!res) { 
            net->other.ip = *ip;
            net->other.port = *port;
            my_printf("Successfully connected!\n");
            return 1;
        }
    }
    return 0;
}

void send_okay(network *net)
{
    int order = OKAY;
    sfPacket_clear(net->packet);
    sfPacket_append(net->packet, &order, sizeof(int));
    char s[20];
    sfIpAddress_toString(net->other.ip, s);
    my_printf("Sending confirmation to: %s at port %d\n", s, net->other.port);
    int res = sfUdpSocket_sendPacket(net->socket, net->packet, net->other.ip, net->other.port);
}

network *init_network(void)
{
    network *net = malloc(sizeof(network));
    net->is_host = 0;
    net->is_multi = 0;
    net->packet = 0;
    net->socket = 0;
    init_orders(net);
    net->other.ip = sfIpAddress_None;
    net->other.port = 0;
    net->is_okay = 1;
    net->selector = sfSocketSelector_create();
    sfTime timeout;
    timeout.microseconds = 1000000;
    net->timeout = timeout;
    net->other.p.test = 0;
    net->other.cscene = -1;
    return net;
}

void init_orders(network *net)
{

    OKAY,
    CONNECTION,
    SYNC,
    POSITION,
    CHANGE_SCENE,
    net->orders[0] = receive_okay;
    net->orders[1] = 0;
    net->orders[2] = 0;
    net->orders[3] = receive_position;
    net->orders[4] = receive_scene;
}
