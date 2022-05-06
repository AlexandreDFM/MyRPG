/*
** EPITECH PROJECT, 2022
** main
** File description:
** Main of rpg
*/

#include "infos.h"

int main(int argc, char **argv)
{
    components all = create_all_components(argc, argv);
    if (all.inf.net->is_multi && !all.inf.net->is_host)
        sync_online(&all);
    while (sfRenderWindow_isOpen(all.inf.win)) {
        handle_music(&all.inf, all.pla);
        handle_scene(&all.inf, all.pla);
        update_events(&all.inf, all.pla);
        update_network(&(all.inf), &all);
    }
    sfRenderWindow_destroy(all.inf.win);
    sfImage_destroy(all.inf.atlases.atlas);
    my_malloc(0); my_sf_free(); fclose(all.inf.log_file);
    my_texture_from_image(NULL, NULL);
    my_image_from_file(NULL);
    my_shader_from_file(NULL, NULL, NULL);
    my_music_from_file(NULL); my_buffer_from_file(NULL);
    return 0;
}
