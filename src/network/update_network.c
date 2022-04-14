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
            void *data = sfPacket_getData(p);
            handle_packet(all, data);
        }
    }
    sfPacket_clear(p);
}

void send_scene(wininf *inf, int scene)
{
    network *net = inf->net;
    net->is_okay = 0;
    int order = CHANGE_SCENE;
    components fcomp;
    fcomp.inf = *inf;
    sfPacket_append(net->packet, &order, sizeof(int));
    sfPacket_append(net->packet, &(inf->net->is_host), sizeof(int));
    sfPacket_append(net->packet, &scene, sizeof(int));
    sfPacket *p = inf->net->packet;
    while (!net->is_okay) {
        sfUdpSocket_sendPacket(net->socket, net->packet, net->other.ip,
            net->other.port);
        int r = sfUdpSocket_receivePacket(net->socket, p, net->ip, &net->port);
        if (!r) {
            net->is_okay = 1;
        }
    }
    sfPacket_clear(net->packet);
}

void send_sync(components *all)
{
    network *net = all->inf.net;
    sfPacket_clear(net->packet);
    my_printf("Asked to sync...\n");
    sfPacket_clear(net->packet);
    int order = SYNC;
    sfPacket_append(net->packet, &order, sizeof(int));
    sfVector2f pos = sfSprite_getPosition(all->pla.test);
    sfPacket_append(net->packet, &pos, sizeof(sfVector2f));
    int poke = all->inf.settings->pokemon;
    sfPacket_append(net->packet, &all->inf.c_scene, sizeof(int));
    sfPacket_append(net->packet, &poke, sizeof(int));
    sfUdpSocket_sendPacket(net->socket, net->packet, net->other.ip,
        net->other.port);
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
                    sfSprite_setPosition(net->other.p.test, *np);
                    net->other.target = *np;
                    all->inf.c_scene = *scene;
                    net->other.cscene = *scene;
                    net->is_okay = 1;
                }
            }
        }
    }
    sfPacket_clear(net->packet);
    my_printf("Synced !\n");
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
    if (*order == CHANGE_SCENE) {
        int *id = data;
        data += sizeof(int);
        if (*id != net->is_host) {
            int *nscene = data;
            net->other.cscene = *nscene;
            int ok = OKAY;
            sfPacket_clear(net->packet);

            sfPacket_append(net->packet, &ok, sizeof(int));
            sfUdpSocket_sendPacket(net->socket, net->packet, net->other.ip,
                net->other.port);
        }
    }
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
