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
    sfIpAddress my_ip = sfIpAddress_getLocalAddress();
    sfIpAddress *addrip = &my_ip;
    int *addrport = &port;
    while (iter <= 1000) {
        sfPacket_clear(inf->net.packet);
        if (!(iter % 100)) {
            my_printf("Trying to connect... (x%d)\n", iter / 100);
        }
        sfPacket_append(inf->net.packet, addrip, sizeof(addrip));
        sfPacket_append(inf->net.packet, addrport, sizeof(addrport));
        sfUdpSocket_sendPacket(inf->net.socket, inf->net.packet, ip, port);
        iter += 1;
    }
}

network init_network(void)
{
    network net;
    net.is_host = 0;
    net.is_multi = 0;
    net.packet = 0;
    net.socket = 0;
    return net;
}
