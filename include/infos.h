/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** INFOS
*/

#ifndef INFOS_H_
#define INFOS_H_

    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <math.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <time.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <stddef.h>

    #define WINDOW_NAME "My RPG"

typedef enum scenes_e {
    HOME,
} scenes;

typedef struct wininf_t {
    enum scenes_e c_scene;
    sfRenderWindow *win;
    sfVideoMode mode;
    sfEvent event;
    struct inputs_t *inputs;
} wininf;

    #include "inputs.h"

void update_events(wininf *inf);
wininf *create_window_infos(void);

#endif /* !INFOS_H_ */
