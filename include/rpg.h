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
    #define APPEND -1

typedef enum scenes_e {
    HOME,
    VILLAGE,
    INTERIOR,
    DOJO,
    BEKIPAN,
    DITTOLAND,
    MAIN_MENU,
    INTRO,
    DITTO,
    DREAM,
    DUNGEON,
} scenes;

typedef enum orders_e {
    OKAY,
    CONNECTION,
    CSYNC,
    POSITION,
    CHANGE_SCENE,
    HSYNC,
    SETPOS,
    COUNT,
} orders;

typedef enum main_menu_t {
    NONE = -1,
    LOAD_SAVE,
    ADVENTURE_LOG,
    OPTIONS,
    KEYBINDS_M,
    CHANGING_KEY,
    EXIT,
    PAUSE,
}m_menu_t;

typedef enum direction_t {
    PUP,
    PUPLEFT,
    PUPRIGHT,
    PDOWN,
    PDOWNLEFT,
    PDOWNRIGHT,
    PLEFT,
    PRIGHT,
    PNONE_DIRECTION,
} direction;

typedef enum menu_indx {
    MAIN_IDX,
    LOAD_IDX,
    OPTIONS_IDX,
    KEYBINDS_IDX,
    PAUSE_VILLAGE_IDX,
    PAUSE_DG_IDX,
}menu_indx;

typedef enum language {
    DEFAULT = -1,
    ENGLISH,
    FRANCAIS,
}language;

typedef struct settings_t {
    int show_collision;
    int pokemon;
    int house;
    int c_fps;
    char **fps;
} settings;

typedef struct atlases_t {
    sfImage *atlas;
    char **pokemons_rect;
    char **pnjs;
    char **icons;
    char **menus_en;
    char **menus_fr;
    char **houses;
    char **statics;
    char **scenes;
    char **collisions;
    char **poke_names;
    char **pokemons_anim;
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
    float intro_anim;
    float intro_anim2;
    float ditto_anim;
    float ditto_anim2;
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
    int offset;
    enum direction_t direction;
    float speed;
    int *slist;
    int **rlist;
    sfIntRect r;
    sfVector2i limit;
    sfSprite *test;
    sfVector2f vel;
    float time;
    sfVector2f nextpos;
} player;

typedef struct camera_t {
    sfView *view;
    sfSprite *target;
    sfVector2f static_p;
    float speed;
} camera;

typedef struct textbox_t {
    int nbr;
    sfSprite *background;
    struct linked_list_t *choices;
} textbox;

typedef struct ui_t {
    sfFont *font;
    sfSprite *test;
    float text_delay;
    sfSprite *background;
    struct linked_list_t *dialog;
} ui;

typedef struct other_t {
    struct player_t p;
    sfVector2f target;
    sfIpAddress ip;
    int cscene;
    int port;
} other;

typedef struct dungeon_t {
    sfImage *img;
    struct map_info *inf;
    int in;
} dungeon;

typedef struct wininf_t {
    sfEvent event;
    int pressed;
    float ftransi;
    int key_change;
    int transition;
    int waiting_key;
    int interacting;
    int change_scene;
    int vol_music;
    int vol_sound;
    int c_fps;
    sfClock *play_time;
    const char **fps;
    const char **key_list;
    dline *playtime;
    sfVideoMode mode;
    sfVector2f next_pos;
    sfKeyCode tmp_key;
    sfRenderWindow *win;
    enum language lang;
    enum scenes_e c_scene;
    enum main_menu_t c_menu;
    enum scenes_e next_scene;
    struct ui_t ui;
    struct network_t *net;
    struct time_inft time;
    struct camera_t camera;
    struct inputs_t inputs;
    struct atlases_t atlases;
    struct dungeon_t dungeon;
    struct scene_t scenes[6];
    struct menus *prev_menu;
    struct menus *main_menu;
    struct menus *load_menu;
    struct menus *pause_menu;
    struct menus *change_keys_menu;
    struct menus *options_menu;
    struct menus *current_menu;
    struct settings_t *settings;
    struct intro_assets_t *intro;
    struct ditto_assets_t *ditto;
    struct dream_assets_t *dream;
    sfRectangleShape *transi;
    void (*triggers[9])(struct wininf_t *win, struct player_t *p);
} wininf;

typedef struct choices_t {
    void *choice;
    void *desc;
    int ptr;
    void (*ptrs[1])(struct wininf_t *);
} choices;

typedef struct menus {
    float blk;
    int id;
    int type;
    int focus;
    int press;
    int offset;
    int max_choice;
    sfSprite *cursor;
    sfVector2f base_pos;
    struct linked_list_t *head;
    struct linked_list_t *texts;
    struct linked_list_t *choices;
    struct linked_list_t *selected;
    struct linked_list_t *backgrounds;
}menuss;

typedef struct components_t {
    struct wininf_t inf;
    struct player_t pla;
} components;

typedef struct network_t {
    int is_multi;
    int is_host;
    int is_okay;
    sfTime timeout;
    sfSocketSelector *selector;
    sfPacket *packet;
    sfUdpSocket *socket;
    sfIpAddress *ip;
    sfIpAddress *any;
    unsigned short port;
    int flags[COUNT - 1];
    int (*orders[7])(char **data, int *important, components *com);
    struct other_t other;
} network;

typedef struct date {
    long int curryear;
    long int extradays;
    long int index;
    long int date;
    long int month;
    long int hours;
    long int minutes;
    long int secondss;
    long int flag;
    long int daystillnow;
    long int extratime;
    int *daysofmonth;
}date_t;

char *unix_to_date(long int seconds);
void set_pokemon(wininf *inf);
void free_musics(wininf *inf);
void end_global_free(components *all);

////////////////////////////////////////////////////////////
//Flags Handling
void change_settings(int opt, char *arg, wininf *inf);
//Flags Handling
int get_settings_flags(int ac, char **av, wininf *win);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Dungeon Generation
int search(int array[], int x, int started);
//Dungeon Generation
void append_list(sfIntRect ***rects, sfIntRect *new_alloc);
//Dungeon Generation
void insert_into(sfUint8 **pixels, int index, int start_x,
int start_y, const sfUint8 *ptr, int y, int line_len, int ref_len);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Utility functions
char *my_itoa(int num);
//Utility functions
int get_arr_len(char **arr);
//Utility functions
float my_atof(char *number);
//Utility functions
char **my_strtwa(char const *str, char *limit);
//Utility functions
void *my_memset(void *dest, int value, int length);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Dialogs Handling
sfIntRect find_icons(wininf *inf, char *str);
//Dialogs Handling
int treat_balise(char *balise, sfColor *color, wininf *inf);
//Dialogs Handling
dline *load_line(char *line, sfFont *font, int size, wininf *inf);
//Dialogs Handling
list *create_dialog_list(wininf *inf, char *path, sfVector2f poubelle);
//Dialogs Handling
void add_icon(sfVector2i origin, sfImage *img, sfIntRect r, sfImage *atlas);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Network functions
void send_okay(network *net);
//Network functions
void init_orders(network *net);
//Network functions
void sync_online(components *all);
//Network functions
void receive_ord(network *net, components *all);
//Network functions
void update_network(wininf *inf, components *all);
//Network functions
void try_to_connect(sfIpAddress ip, int port, wininf *inf);
//Network functions
void add_ord(int ord, void *data, int size, sfPacket *packet);
//Network functions
int receive_with_timeout(network *net, sfIpAddress *ip, unsigned short *port);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Collision Handling
void add_collisions(char *str, list **l);
//Collision Handling
int check_rect_col(collision *self, sfVector2f pos);
//Collision Handling
int check_circle_col(collision *self, sfVector2f pos);
//Collision Handling
void add_circle_col(list **l, int radius, int x, int y);
//Collision Handling
void add_rect_col(list **l, sfVector2f pos, sfVector2f size);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Drawing functions
void draw_home(wininf *inf);
//Drawing functions
void draw_player(wininf *inf, player *p);
//Drawing functions
void draw_menu(wininf *inf, menuss *menu);
//Drawing functions
void move_cursor(menuss *menu, wininf *inf);
//Drawing functions
void handle_scene(wininf *infos, player *p);
//Drawing functions
void draw_static_scene(wininf *inf, scene s);
//Drawing functions
void update_transition(wininf *inf, player p);
//Drawing functions
void draw_rect_col(collision *self, sfRenderWindow *win);
//Drawing functions
void draw_circle_col(collision *self, sfRenderWindow *win);
//Drawing functions
void draw_choices(wininf *inf, list *choices_l, list *head);
//Drawing functions
void draw_entity(time_info *time_s, list *obj, sfRenderWindow *win);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Initializations
network *init_network(void);
//Initializations
settings *init_settings(void);
//Initializations
void init_inputs(wininf *inf);
//Initializations
void init_times(wininf *infos);
//Initializations
void init_textbox(wininf *win);
//Initializations
camera init_camera(wininf inf);
//Initializations
void create_atlases(wininf *inf);
//Initializations
void create_triggers(wininf *inf);
//Initializations
player init_player(wininf inf, int id);
//Initializations
scene create_home(wininf *infos, int id);
//Initializations
entity *create_entity(wininf *info, int id);
//Initializations
wininf create_window_infos(int ac, char **av);
//Initializations
void add_pnjs(atlases atlas, int idx, scene *s);
//Initializations
scene create_static_env(wininf *inf, int id);
//Initializations
void create_pnj(char *line, scene *s, atlases atlas);
//Initializations
components create_all_components(int ac, char **argv);
//Initializations
sfSprite *atlas_to_sprite(sfIntRect rect, sfImage *atlas);
//Initializations
void place_decorations(char *line, sfImage *atlas, char **csv, list **l);
//Initializations
void create_static_anim(sfImage *atlas, char *name, list **l, char **csv);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Updates
void update_inputs(wininf *inf);
//Updates
void update_time(wininf *infos);
//Updates
void update_keyboard(wininf *inf);
//Updates
void update_joysticks(wininf *inf);
//Updates
void update_events(wininf *inf, player *p);
//Updates
void update_camera(wininf *inf);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Linked lists
void push_back(list **l, void *new_data);
//Linked lists
void add_to_list(list **l, void *new_elem);
//Linked lists
void draw_list(list *obj, sfRenderWindow *win);
//Linked lists
void push_back_double(list **l, void *new_data);
//Linked lists
list *init_circular(char **arr, wininf *inf, sfVector2f pos, sfVector2f pos2);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Teleporters
void ta_mere(wininf *win, player *p);
//Teleporters
void interact_pnj(wininf *win, player *p);
//Teleporters
void sleep_and_save(wininf *win, player *p);
//Teleporters
void village_to_dojo(wininf *win, player *p);
//Teleporters
void homeext_to_village(wininf *win, player *p);
//Teleporters
void homeext_to_homeint(wininf *win, player *p);
//Teleporters
void village_to_bekipan(wininf *win, player *p);
//Teleporters
void village_to_dittoland(wininf *win, player *p);
//Teleporters
void generate_random_dungeon(wininf *win, player *p);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
//Menu pointers
void play(wininf *inf);
//Menu pointers
void a_log(wininf *inf);
//Menu pointers
void no_but(wininf *inf);
//Menu pointers
void go_back(wininf *inf);
//Menu pointers
void options(wininf *inf);
//Menu pointers
void my_exit(wininf *inf);
//Menu pointers
void yes_but(wininf *inf);
//Menu pointers
void go_main(wininf *inf);
//Menu pointers
void go_keybinds(wininf *inf);
//Menu pointers
void change_volume(wininf *inf);
//Menu pointers
void change_keybind(wininf *inf);
//Menu pointers
void init_load_pointers(wininf *inf);
//Menu pointers
void init_options_pointers(wininf *inf);
//Menu pointers
void init_main_menu_pointers(wininf *inf);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Maths Functions
int length_of_int(int a);
//Maths Functions
float my_repeat(float t, float mag);
//Maths Functions
float my_pingpong(float t, float mag);
//Maths Functions
float my_lerpf(float a, float b, float t);
//Maths Functions
float distance(sfVector2f a, sfVector2f b);
//Maths Functions
float my_clamp(float d, float min, float max);
//Maths Functions
float manhattan_distance(sfVector2f a, sfVector2f b);
//Maths Functions
sfVector2f my_lerp(sfVector2f a, sfVector2f b, float t);
//Maths Functions
int is_same(sfVector2f v1, sfVector2f v2, float threshold);
//Maths Functions
int is_valid(list *c, sfVector2f pos, sfVector2f *v, wininf *inf, player *p);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Generate textboxes
void topbot_border(sfVector2i size, sfImage *new);
//Generate textboxes
void leftright_border(sfVector2i size, sfImage *new);
//Generate textboxes
sfSprite *generate_textbox(sfVector2i size, sfImage *atlas);
//Generate textboxes
void add_corner(sfImage *img, sfImage *atlas, sfVector2i pos, sfVector2i glo);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Menu initialization
void update_playtime(wininf *inf);
//Menu initialization
list *init_backgrounds(char **arr, wininf *inf);
//Menu initialization
menuss *init_ig_menus(wininf *inf, int menu_id, int focus);
//Menu initialization
menuss *init_all_menus(wininf *inf, int menu_id, int focus);
//Menu initialization
sfSprite *set_cursor(wininf *inf, sfVector2f scale, sfVector2f pos);
//Menu initialization
sfText *init_text(char *str, sfFont *font, sfVector2f pos, int size);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Network pointers
int receive_okay(char **data, int *important, components *all);
//Network pointers
int receive_scene(char **data, int *important, components *all);
//Network pointers
int receive_position(char **data, int *important, components *all);
//Network pointers
int receive_connection(char **data, int *important, components *all);
//Network pointers
int receive_clientsync(char **data, int *important, components *all);
//Network pointers
int receive_hostsync(char **data, int *important, components *all);
//Network pointers
int receive_setposition(char **data, int *important, components *all);
////////////////////////////////////////////////////////////

void draw_intro(wininf *inf);
void treat_axis(wininf *inf);
void draw_dungeon(wininf *inf, player *p);

int get_int_len(long long int nbr);
sfIntRect move_rect_player(player p);
int pos_char(char *string, char *presence);
char *my_strdup_to_char(char *src, char *delim);
void perform_free_movement(wininf *inf, player *p);
void perform_dungeon_movement(wininf *inf, player *p);
void center_menu(menuss *menu, wininf *inf, player *p);
void player_direction_management(wininf *inf, player *p);
char *my_slice_array(int direction, char *strslice, int nbslice);

#endif
