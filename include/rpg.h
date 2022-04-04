/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** rpg
*/

#ifndef RPG_H_
#define RPG_H_

    #include "infos.h"
    #include "atlas.h"
    #include "entity.h"
    #include "inputs.h"
    #include "my.h"
    #include "math.h"
    #include "printf.h"
    #include "scenes.h"
    #include "types.h"

typedef enum scenes_e {
    HOME,
    VILLAGE,
    INTERIOR,
} scenes;

typedef struct atlases_t {
    sfImage *atlas;
    char **statics;
    char **collisions;
    char **scenes;
    char **pokemons_anim;
    char **houses;
    char **pnjs;
} atlases;

typedef struct collision_t {
    int (*check)(struct collision_t *self, sfVector2f pos);
    void (*draw)(struct collision_t *self, sfRenderWindow *win);
    sfVector2i pos;
    sfVector2i size;
    int radius;
    sfRectangleShape *rect;
    sfCircleShape *circle;
    int auto_trigger;
    int ptr;
} collision;

typedef struct time_inft {
    sfClock *dt_cal;
    float dt;
    float transi;
    float time;
    float anim;
} time_info;

typedef struct linked_list_t {
    void *data;
    struct linked_list_t *next;
} list;

typedef struct scene_t {
    struct linked_list_t *statics;
    struct linked_list_t *animated;
    struct linked_list_t *colls;
} scene;

typedef struct player_t {
    sfSprite *test;
    sfVector2f vel;
    float speed;
} player;

typedef struct camera_t {
    sfView *view;
    sfSprite *target;
    sfVector2f static_p;
    float speed;
} camera;

typedef struct wininf_t {
    sfEvent event;
    int transition;
    sfVideoMode mode;
    sfRenderWindow *win;
    struct scene_t scenes[3];
    enum scenes_e c_scene;
    enum scenes_e next_scene;
    sfVector2f next_pos;
    struct time_inft time;
    struct camera_t camera;
    struct inputs_t inputs;
    struct atlases_t atlases;
    int change_scene;
    sfRectangleShape *transition_rect;
    void (*triggers[4])(struct wininf_t *win);
} wininf;


typedef struct components_t {
    struct wininf_t inf;
    struct player_t pla;
} components;

void draw_home(wininf *inf);
void init_inputs(wininf *inf);
camera init_camera(wininf inf);
void init_times(wininf *infos);
void update_inputs(wininf *inf);
void update_time(wininf *infos);
void update_events(wininf *inf);
void create_atlases(wininf *inf);
void update_keyboard(wininf *inf);
void update_joysticks(wininf *inf);
wininf create_window_infos(char **av);
player init_player(wininf inf, int id);
void draw_player(wininf *inf, player p);
float my_lerpf(float a, float b, float t);
void add_collisions(char *str, list **l);
scene create_home(wininf *infos, int id);
void handle_scene(wininf *infos, player p);
float distance(sfVector2f a, sfVector2f b);
void add_to_list(list **l, void *new_elem);
entity *create_entity(wininf *info, int id);
void draw_static_scene(wininf *inf, scene s);
components create_all_components(char **argv);
void update_transition(wininf *inf, player p);
char **my_strtwa(char const *str, char *limit);
void draw_list(list *obj, sfRenderWindow *win);
int check_rect_col(collision *self, sfVector2f pos);
scene create_static_environment(wininf *inf, int id);
int check_circle_col(collision *self, sfVector2f pos);
sfVector2f my_lerp(sfVector2f a, sfVector2f b, float t);
void add_circle_col(list **l, int radius, int x, int y);
void draw_rect_col(collision *self, sfRenderWindow *win);
sfSprite *atlas_to_sprite(sfIntRect rect, sfImage *atlas);
void draw_circle_col(collision *self, sfRenderWindow *win);
void add_rect_col(list **l, sfVector2f pos, sfVector2f size);
void draw_entity(time_info *time_s, list *obj, sfRenderWindow *win);
void place_decorations(char *line, sfImage *atlas, char **csv, list **l);
void create_static_anim(sfImage *atlas, char *name, list **l, char **csv);
void update_camera(camera c, float dt, sfRenderWindow *win, sfRectangleShape *transi);
int check_if_valid_movement(list *cols, sfVector2f pos, sfVector2f *vel, wininf *win);

void ta_mere(wininf *win);
void sleep_and_save(wininf *win);
void homeext_to_village(wininf *win);
void homeext_to_homeint(wininf *win);

//MATHS
float my_repeat(float t, float mag);
float my_pingpong(float t, float mag);
float my_clamp(float d, float min, float max);

#endif
