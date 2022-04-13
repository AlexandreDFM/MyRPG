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
    while (iter <= 1000) {
        sfPacket_clear(net->packet);
        sfPacket_append(net->packet, addrip, sizeof(sfIpAddress));
        sfPacket_append(net->packet, addrport, sizeof(int));
        sfUdpSocket_sendPacket(net->socket, net->packet, ip, port);
        if (!(iter % 500)) {
            my_printf("Trying to connect... (x%d)\n", iter / 500);
        }
        //MB SLEEP
        sfPacket_clear(net->packet);
        int res = sfUdpSocket_receivePacket(net->socket, net->packet, otherip, addrport);
        if (!res) {
            net->other.ip = ip;
            net->other.port = port;
            printf("Successfully connected!\n");
            break;
        }
        iter += 1;
    }
}

void send_okay(network *net)
{
    int order = OKAY;
    sfPacket_clear(net->packet);
    sfPacket_append(net->packet, &order, sizeof(int));
    char ipstr[20];
    sfIpAddress_toString(net->other.ip, ipstr);
    printf("Sending confirmation to: %s at port %d\n", ipstr, net->other.port);
    int res = sfUdpSocket_sendPacket(net->socket, net->packet, net->other.ip, net->other.port);
}

network *init_network(void)
{
    network *net = malloc(sizeof(network));
    net->is_host = 0;
    net->is_multi = 0;
    net->packet = 0;
    net->socket = 0;
    net->other.ip = sfIpAddress_None;
    net->other.port = 0;
    return net;
}
