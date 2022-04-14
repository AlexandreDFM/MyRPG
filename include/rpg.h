/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** rpg
*/

#ifndef RPG_H_
#define RPG_H_

    #include "infos.h"
    #include "dungeon.h"
    #include "atlas.h"
    #include "entity.h"
    #include "inputs.h"
    #include "my.h"
    #include "math.h"
    #include "printf.h"
    #include "scenes.h"
    #include "types.h"
    #include "dialog.h"

typedef enum scenes_e {
    HOME,
    VILLAGE,
    INTERIOR,
    DOJO,
    BEKIPAN,
    DITTOLAND,
    MAIN_MENU
} scenes;

typedef enum orders_e {
    OKAY,
    CONNECTION,
    SYNC,
    POSITION,
    CHANGE_SCENE,
} orders;

typedef enum main_menu_t {
    NONE = -1,
    LOAD_SAVE,
    ADVENTURE_LOG,
    OPTIONS,
    EXIT,
}m_menu_t;

typedef struct settings_t {
    int show_collision;
    int pokemon;
    int house;
} settings;

typedef struct atlases_t {
    sfImage *atlas;
    char **statics;
    char **collisions;
    char **scenes;
    char **pokemons_anim;
    char **houses;
    char **pnjs;
    char **icons;
    char **menus;
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

typedef struct pnj_t {
    sfVector2f pos;
    entity *ent;
    char *dialog;
} pnj;

typedef struct linked_list_t {
    void *data;
    struct linked_list_t *next;
    struct linked_list_t *prev;
} list;

typedef struct scene_t {
    struct linked_list_t *pnjs;
    struct linked_list_t *colls;
    struct linked_list_t *statics;
    struct linked_list_t *animated;
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

typedef struct textbox_t {
    sfSprite *background;
    int nbr;
    struct linked_list_t *choices;
} textbox;

typedef struct ui_t {
    sfSprite *background;
    sfFont *font;
    float text_delay;
    sfSprite *test;
    struct linked_list_t *dialog;
} ui;

typedef struct other_t {
    struct player_t p;
    sfVector2f target;
    sfIpAddress ip;
    int cscene;
    int port;
} other;

typedef struct network_t {
    int is_multi;
    int is_host;
    int is_okay;
    sfTime timeout;
    sfSocketSelector *selector;
    sfPacket *packet;
    sfUdpSocket *socket;
    sfIpAddress *ip;
    unsigned short port;
    struct other_t other;
} network;

typedef struct wininf_t {
    sfEvent event;
    int transition;
    int interacting;
    int change_scene;
    int menu_padding;
    sfVideoMode mode;
    sfVector2f next_pos;
    sfRenderWindow *win;
    enum scenes_e c_scene;
    enum main_menu_t c_menu;
    enum scenes_e next_scene;
    struct ui_t ui;
    struct network_t *net;
    struct time_inft time;
    struct camera_t camera;
    struct inputs_t inputs;
    struct atlases_t atlases;
    struct scene_t scenes[6];
    struct menus *current_menu;
    struct menus *main_menu;
    struct menu_t *load_menu;
    struct menu_t *first_menu;
    struct settings_t *settings;
    sfRectangleShape *transition_rect;
    void (*triggers[9])(struct wininf_t *win, struct player_t p);
} wininf;

typedef struct choices_t {
    sfText *choice;
    sfText *desc;
    int ptr;
    void (*ptrs[1])(struct wininf_t *);
} choices;


typedef struct menu_t {
    sfSprite *background;
    sfSprite *background2;
    sfSprite *background3;
    sfSprite *cursor;
    struct linked_list_t *head;
    struct linked_list_t *choices;
    struct linked_list_t *selected;
    struct choices_t *current;
    void (*ptrs[5])(struct wininf_t *);
    int max_choice;
    int curr_choice;
    sfVector2f base_pos;
    int pressed;
    float blink;
} menus;

typedef struct menus {
    float blink;
    int pressed;
    int max_choice;
    sfSprite *cursor;
    sfVector2f base_pos;
    struct linked_list_t *head;
    struct linked_list_t *choices;
    struct linked_list_t *selected;
    struct linked_list_t *backgrounds;
}menuss;

typedef struct components_t {
    struct wininf_t inf;
    struct player_t pla;
} components;

int length_of_int(int a);
network *init_network(void);
void draw_menu(wininf *inf);
void draw_home(wininf *inf);
settings *init_settings(void);
void init_inputs(wininf *inf);
camera init_camera(wininf inf);
void init_times(wininf *infos);
void init_textbox(wininf *win);
void update_inputs(wininf *inf);
void update_time(wininf *infos);
void update_events(wininf *inf);
void create_atlases(wininf *inf);
void create_triggers(wininf *inf);
void update_keyboard(wininf *inf);
void update_joysticks(wininf *inf);
player init_player(wininf inf, int id);
void send_scene(wininf *inf, int scene);
void draw_player(wininf *inf, player p);
void add_collisions(char *str, list **l);
scene create_home(wininf *infos, int id);
void push_back(list **l, void *new_data);
float my_lerpf(float a, float b, float t);
void move_cursor(menuss *menu, wininf *inf);
menus *init_menu(wininf *inf, int menu_id);
float distance(sfVector2f a, sfVector2f b);
void add_to_list(list **l, void *new_elem);
void handle_scene(wininf *infos, player *p);
entity *create_entity(wininf *info, int id);
void draw_static_scene(wininf *inf, scene s);
sfIntRect find_icons(wininf *inf, char *str);
wininf create_window_infos(int ac, char **av);
void update_transition(wininf *inf, player p);
char **my_strtwa(char const *str, char *limit);
void draw_list(list *obj, sfRenderWindow *win);
void add_pnjs(atlases atlas, int idx, scene *s);
menus *init_load_menu(wininf *inf, int menu_id);
void push_back_double(list **l, void *new_data);
void update_network(wininf *inf, components *all);
int check_rect_col(collision *self, sfVector2f pos);
scene create_static_environment(wininf *inf, int id);
void create_pnj(char *line, scene *s, atlases atlas);
components create_all_components(int ac, char **argv);
int check_circle_col(collision *self, sfVector2f pos);
int get_settings_flags(int ac, char **av, wininf *win);
sfVector2f my_lerp(sfVector2f a, sfVector2f b, float t);
void add_circle_col(list **l, int radius, int x, int y);
void draw_rect_col(collision *self, sfRenderWindow *win);
sfSprite *atlas_to_sprite(sfIntRect rect, sfImage *atlas);
void try_to_connect(sfIpAddress ip, int port, wininf *inf);
void draw_circle_col(collision *self, sfRenderWindow *win);
sfText *init_text(char *str, sfFont *font, sfVector2f pos);
void draw_choices(wininf *inf, list *choices_l, list *head);
int treat_balise(char *balise, sfColor *color, wininf *inf);
sfSprite *generate_textbox(sfVector2i size, sfImage *atlas);
void add_rect_col(list **l, sfVector2f pos, sfVector2f size);
dline *load_line(char *line, sfFont *font, int size, wininf *inf);
int receive_with_timeout(network *net, sfIpAddress *ip, int *port);
void draw_entity(time_info *time_s, list *obj, sfRenderWindow *win);
sfSprite *set_cursor(wininf *inf, sfVector2f scale, sfVector2f pos);
list *create_dialog_list(wininf *inf, char *path, sfVector2f poubelle);
void place_decorations(char *line, sfImage *atlas, char **csv, list **l);
void create_static_anim(sfImage *atlas, char *name, list **l, char **csv);
void add_icon(sfVector2i origin, sfImage *img, sfIntRect r, sfImage *atlas);
list *init_circular(char **arr, wininf *inf, sfVector2f pos, sfVector2f pos2);
void update_camera(camera c, float dt, sfRenderWindow *w, sfRectangleShape *t);
int is_valid(list *cols, sfVector2f pos, sfVector2f *vel, wininf *inf, player p);

void ta_mere(wininf *win, player p);
void interact_pnj(wininf *win, player p);
void sleep_and_save(wininf *win, player p);
void village_to_dojo(wininf *win, player p);
void homeext_to_village(wininf *win, player p);
void homeext_to_homeint(wininf *win, player p);
void village_to_bekipan(wininf *win, player p);
void village_to_dittoland(wininf *win, player p);
void generate_random_dungeon(wininf *win, player p);

//POINTERS
void play(wininf *inf);
void a_log(wininf *inf);
void no_but(wininf *inf);
void options(wininf *inf);
void my_exit(wininf *inf);
void yes_but(wininf *inf);
void init_load_pointers(wininf *inf);
void init_main_menu_pointers(wininf *inf);

//MATHS
float my_repeat(float t, float mag);
float my_pingpong(float t, float mag);
float my_clamp(float d, float min, float max);
float manhattan_distance(sfVector2f a, sfVector2f b);
float my_lerpf(float a, float b, float t);

//TEXTBOXES
void topbot_border(sfVector2i size, sfImage *new);
void leftright_border(sfVector2i size, sfImage *new);
sfSprite *generate_textbox(sfVector2i size, sfImage *atlas);
void add_corner(sfImage *img, sfImage *atlas, sfVector2i pos, sfVector2i glo);

menuss *init_all_menus(wininf *inf, int menu_id);
int is_same(sfVector2f v1, sfVector2f v2, float threshold);

#endif
