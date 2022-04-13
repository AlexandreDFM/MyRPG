/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** flags_handling
*/

#include "rpg.h"
#include <getopt.h>
#include <unistd.h>

int get_settings_flags(int ac, char **av, wininf *win)
{
    static struct option lo[] = {{"collisions", no_argument, NULL, 'C'},
                            {"pokemon", required_argument, NULL, 'p'},
                            {"house", required_argument, NULL, 'H'},
                            {"client", required_argument, NULL, 1001},
                            {"host", no_argument, NULL, 1000}};
    int opt = 0;
    while ((opt = getopt_long(ac, av, "H:C:p", lo, NULL)) != -1) {
        change_settings(opt, optarg, win);
    }
    if (win->net->is_multi && win->net->is_host) {
        printf("Before FIP: %d\n", win->net->port);
    }
    return 0;
}

void change_settings(int opt, char *arg, wininf *inf)
{
    if (opt == 'p')
        inf->settings->pokemon = my_atoi(arg);
    if (opt == 'H')
        inf->settings->house = my_atoi(arg);
    if (opt == 'C')
        inf->settings->show_collision = 1;
    if (opt == 1001) {
        int len = 0;
        for (; arg[len] != ':'; len++);
        arg += len;
        int port = my_atoi(arg + 1);
        inf->net->packet = sfPacket_create();
        arg -= len; arg[len] = '\0';
        inf->net->is_host = 0;
        inf->net->is_multi = 1;
        inf->net->socket = sfUdpSocket_create();
        sfIpAddress ip = sfIpAddress_fromString(arg);
        try_to_connect(ip, port, inf);
    }
    if (opt == 1000) {
        sfIpAddress ip = sfIpAddress_getLocalAddress();
        my_printf("Starting server side on your local address at 7878...\n");
        inf->net->is_host = 1;
        inf->net->is_multi = 1;
        inf->net->packet = sfPacket_create();
        inf->net->socket = sfUdpSocket_create();
        inf->net->ip = malloc(sizeof(sfIpAddress));
        *inf->net->ip = ip;
        inf->net->port = 7878;
        sfUdpSocket_setBlocking(inf->net->socket, sfFalse);
        char ipstr[40];
        sfIpAddress_toString(ip, ipstr);
        printf("Binding to %s\n", ipstr);
        sfUdpSocket_bind(inf->net->socket, inf->net->port, ip);
    }
}
