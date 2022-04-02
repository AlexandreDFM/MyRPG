/*
** EPITECH PROJECT, 2022
** main
** File description:
** Main of rpg
*/

#include "infos.h"
#include <SFML/OpenGL.h>
#include "scenes.h"

int main(int argc, char **argv)
{
    components all = create_all_components(argv);
    glEnable(GL_BLEND);
    while (sfRenderWindow_isOpen(all.inf.win)) {
        handle_scene(&(all.inf), all.pla);
        update_events(&(all.inf));
    }
    sfRenderWindow_destroy(all.inf.win);
    sfImage_destroy(all.inf.atlases.atlas);
    return 0;
}
