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
                            {"host", no_argument, NULL, 1000},
                            {"language", required_argument, NULL,'l'},
                            {"framerate", required_argument, NULL, 'f'}};
    int opt = 0;
    while ((opt = getopt_long(ac, av, "H:C:p:l:f:", lo, NULL)) != -1) {
        change_settings(opt, optarg, win);
    }
    return 0;
}

void manage_fps(char *arg, wininf *inf)
{
    int i = 0;
    for (; i < 6 && my_strcmp(my_strlowcase(arg),
    my_strlowcase(inf->settings->fps[i])) != 0; i++);
    inf->settings->fps[5][0] = 'M';
    if (i == 6) {
        my_printf("Framerate not found, defaulting to 60\n");
        inf->settings->c_fps = 1;
    } else {
        inf->settings->c_fps = i;
    }
}

void manage_lang(char *arg, wininf *inf)
{
    if (my_strcmp(arg, "en") == 0){
        inf->lang = ENGLISH;
    } else if (my_strcmp(arg, "fr") == 0){
        inf->lang = FRANCAIS;
    } else {
        inf->lang = DEFAULT;
        my_printf("Language not found, defaulting to English\n");
    }
}

void manage_host(char *arg, wininf *inf)
{
    sfIpAddress ip = sfIpAddress_getLocalAddress();
    my_printf("Starting server side on your local address at 7878...\n");
    inf->net->is_host = 1;
    inf->net->is_multi = 1;
    inf->net->packet = sfPacket_create();
    inf->net->socket = sfUdpSocket_create();
    inf->net->ip = malloc(sizeof(sfIpAddress));
    *inf->net->ip = ip;
    inf->net->port = PORT;
    char ipstr[40];
    sfIpAddress_toString(ip, ipstr);
    printf("Binding to %s\n", ipstr);
    sfUdpSocket_setBlocking(inf->net->socket, sfFalse);
    sfUdpSocket_bind(inf->net->socket, inf->net->port, ip);
    sfSocketSelector_addUdpSocket(inf->net->selector, inf->net->socket);
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
        sfUdpSocket_setBlocking(inf->net->socket, sfFalse);
        try_to_connect(ip, port, inf);
    }
    if (opt == 1000) manage_host(arg, inf);
    if (opt == 'l') manage_lang(arg, inf);
    if (opt == 'f') manage_fps(arg, inf);
}
