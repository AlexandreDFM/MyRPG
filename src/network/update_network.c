/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** update_network
*/

#include "rpg.h"

void update_network(wininf *inf)
{
    if (!inf->net.is_multi) return;
    sfPacket *p = inf->net.packet;
    sfPacket_clear(p);
    int res = sfUdpSocket_receivePacket(inf->net.socket, p, inf->net.ip, inf->net.port);
    if (res == sfSocketDone) {
        void *data = sfPacket_getData(p);
        sfIpAddress *client_ip = data;
        data += sizeof(client_ip);
        int *port = data;
        char ipstr[20];
        sfIpAddress_toString(*client_ip, ipstr);
        printf("Received message from client %s at port %d !!!!!!\n", ipstr, *port);
    }
}
