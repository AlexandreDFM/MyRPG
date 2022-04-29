/*
** EPITECH PROJECT, 2022
** main
** File description:
** Main of rpg
*/

#include "infos.h"
#include "scenes.h"

int main(int argc, char **argv)
{
    char *str = unix_to_date(time(0));
    components all = create_all_components(argc, argv);
    if (all.inf.net->is_multi && !all.inf.net->is_host)
        sync_online(&all);
    while (sfRenderWindow_isOpen(all.inf.win)) {
        handle_scene(&all.inf, &all.pla);
        update_events(&all.inf, &all.pla);
        update_network(&(all.inf), &all);
    }
    sfRenderWindow_destroy(all.inf.win);
    sfImage_destroy(all.inf.atlases.atlas);
    return 0;
}
