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
    sfSprite *stairs;
    char **map;
    int **dsts;
    sfIntRect **rooms;
    int nbr_rooms;
    sfVector2f starting_pos;
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
int get_current_roomlo(sfVector2i pos, map_inf *inf);
sfVector2f get_random_position(sfIntRect **rooms, int count);
unsigned char get_neighbours(int i, int o, char **tab, int len);
sfImage *generate_map_image(char **map, int line_len, sfImage *filename);
int get_current_room(sfVector2f pos, map_inf *inf);
sfVector2i get_closest_exit(int room, sfVector2f target, map_inf *inf);
sfIntRect generate_room(sfIntRect *rect);
sfIntRect **random_split(sfIntRect *r, int iter);
bsp *split_container(sfIntRect *main, int iter);
bsp *build_bsp(int size, int iter);
int is_leaf(bsp *tree);
char **empty_map(int size);
map_inf *generate_map(int iter, sfImage *atlas, sfImage *atlas2);
sfIntRect generate_room(sfIntRect *rect);
sfIntRect **random_split(sfIntRect *r, int iter);
void clean_map(char ***mapref);
sfIntRect get_center(sfIntRect *rect);
void free_list(sfIntRect **rects);
void fill_lre(sfIntRect *l, sfIntRect *re, sfIntRect *r, sfIntRect** splits);
int rdm_btw(int min, int max);
void populate_map(char ***map, bsp *tree, sfIntRect ***rects, int *count);
void get_paths(char ***map, bsp *tree);
void fill_map(sfIntRect rect, char ***map);
void populate_map(char ***map, bsp *tree, sfIntRect ***rects, int *count);

#endif /* !DEBUG_H_ */
