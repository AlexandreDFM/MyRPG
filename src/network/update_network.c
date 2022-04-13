/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** update_network
*/

#include "rpg.h"

void update_network(wininf *inf)
{
    network *net = inf->net;
    if (!net->is_host) return;
    if (!inf->net->is_multi) return;
    sfPacket *p = inf->net->packet;
    sfPacket_clear(p);
    char ipstr[40];
    sfIpAddress_toString(*net->ip, ipstr);
    int res = sfUdpSocket_receivePacket(net->socket, p, net->ip, &net->port);
    if (res == sfSocketDone) {
        printf("Receiving on %s\n", ipstr);
        void *data = sfPacket_getData(p);
        sfIpAddress *client_ip = (sfIpAddress*)data;
        data += sizeof(sfIpAddress);
        int *port = data;
        net->other.ip = *client_ip;
        net->other.port = *port;
        send_okay(net);
    }
}
