/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** handle_orders
*/

#include "rpg.h"

int receive_connection(char **data, int *important, components *all)
{
    my_printf(stdout, "Incomming connection...\n");
    *important = 1;
    sfIpAddress *client_ip = (sfIpAddress*)(*data);
    *data += sizeof(sfIpAddress);
    int *port = (int *)*data;
    network *net = all->inf.net;
    net->other.ip = *client_ip;
    net->other.port = *port;
    net->other.connected = 1;
    sfPacket_append(all->inf.net->packet, port, sizeof(int));
    sfUdpSocket_sendPacket(net->socket, net->packet, net->other.ip,
        net->other.port);
    sfPacket_clear(net->packet);
    return sizeof(int) * 2 + sizeof(sfIpAddress);
}

int receive_position(char **data, int *important, components *all)
{
    all->inf.net->other.target = *((sfVector2f*)*data);
    *data += sizeof(sfVector2f);
    return sizeof(int) + sizeof(sfVector2f);
}

int receive_setposition(char **data, int *important, components *all)
{
    sfVector2f np = *((sfVector2f *)*data);
    all->inf.net->other.p->target = np;
    sfSprite_setPosition(all->inf.net->other.p->test, np);
    *data += sizeof(sfVector2f);
    return sizeof(int) + sizeof(sfVector2f);
}

int receive_scene(char **data, int *important, components *all)
{
    int ord_to_remove = *((int *)*data);
    all->inf.net->other.cscene = ord_to_remove;
    all->inf.net->flags[ord_to_remove] = 0;
    *data += sizeof(int);
    return sizeof(int) * 2;
}

int receive_dungeon_info(char **data, int *important, components *all)
{
    map_inf *inf = ((map_inf *)*data);
    *data += sizeof(map_inf);
    int id = *((int *)*data);
    *data += sizeof(int);
    my_printf(stdout, "Received map of id: %d\n", id);
    for (int i = 0; inf->map[i]; i++) {
        my_printf(stdout, "%s\n", inf->map[i]);
    }
    return sizeof(int) + sizeof(map_inf);
}
