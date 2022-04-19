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

typedef struct map_info{
    sfTexture *texture;
    char **map;
    sfIntRect **rooms;
    int nbr_rooms;
}map_inf;

typedef struct bsp_s{
    sfIntRect *rect;
    struct bsp_s *left;
    struct bsp_s *right;
} bsp;

int is_leaf(bsp *tree);
sfVector2i apply_dir(int dir, char **map);
sfIntRect **random_split(sfIntRect *rect);
char **my_str_to_word_array(char const *str);
unsigned char get_neighbours(int i, int o, char **tab, int len);
sfImage *generate_map_image(char **map, int line_len, sfImage *filename);
sfVector2f **get_random_position(sfIntRect **rooms, int count, char ***map);

#endif /* !DEBUG_H_ */
