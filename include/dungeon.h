/*
** EPITECH PROJECT, 2022
** RedDungeon
** File description:
** debug
*/

#ifndef DEBUG_H_
#define DEBUG_H_

    #include "rpg.h"
    #define SIGN(x) ((x < 0) ? -1 : 1)
    #define MAP_SIZE 50
    #define H_RATIO 0.45
    #define W_RATIO 0.45

enum directions {
    RIGHT = 1,
    LEFT = 2,
    UP = 4,
    DOWN = 8
};

typedef struct map_info {
    sfSprite *sp;
    char **map;
    int **dsts;
    sfIntRect **rooms;
    int nbr_rooms;
    sfVector2f **pos;
} map_inf;

typedef struct bsp_s {
    sfIntRect *rect;
    struct bsp_s *left;
    struct bsp_s *right;
} bsp;

int is_leaf(bsp *tree);
sfVector2f local_to_global(int x, int y);
sfVector2i global_to_local(sfVector2f p);
sfVector2i apply_dir(int dir, char **map);
sfIntRect **random_split(sfIntRect *rect, int iter);
char **my_str_to_word_array(char const *str);
map_inf *generate_map(int iter, sfImage *atlas);
unsigned char get_neighbours(int i, int o, char **tab, int len);
sfImage *generate_map_image(char **map, int line_len, sfImage *filename);
sfVector2f **get_random_position(sfIntRect **rooms, int count, char ***map);
int get_current_room(sfVector2f pos, map_inf *inf);
void get_closest_exit(int room, sfVector2f target, map_inf *inf);

#endif /* !DEBUG_H_ */
