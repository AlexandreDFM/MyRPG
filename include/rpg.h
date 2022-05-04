/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** rpg
*/

#ifndef RPG_H_
#define RPG_H_
#define my_sprite() my_sfalloc((void *(*)(void))sfSprite_create,\
    (void *(*)(void *))sfSprite_destroy)
#define my_texture() my_sfalloc((void *(*)(void))sfTexture_create,\
    (void *(*)(void *))sfTexture_destroy)
#define my_font() my_sfalloc((void *(*)(void))sfFont_createFromFile,\
    (void *(*)(void *))sfFont_destroy)
#define my_music() my_sfalloc((void *(*)(void))sfMusic_createFromFile,\
    (void *(*)(void *))sfMusic_destroy)
#define my_sound() my_sfalloc((void *(*)(void))sfSound_create,\
    (void *(*)(void *))sfSound_destroy)
#define my_text() my_sfalloc((void *(*)(void))sfText_create,\
    (void *(*)(void *))sfText_destroy)
#define my_rectangle() my_sfalloc((void *(*)(void))sfRectangleShape_create,\
    (void *(*)(void *))sfRectangleShape_destroy);
#define my_circle() my_sfalloc((void *(*)(void))sfCircleShape_create,\
    (void *(*)(void *))sfCircleShape_destroy)
#define my_clock() my_sfalloc((void *(*)(void))sfClock_create,\
    (void *(*)(void *))sfClock_destroy)
#define my_view() my_sfalloc((void *(*)(void))sfView_create,\
    (void *(*)(void *))sfView_destroy)
#define my_socket() my_sfalloc((void *(*)(void))sfSocket_create,\
    (void *(*)(void *))sfSocket_destroy)
#define my_sock_select() my_sfalloc((void *(*)(void))sfSocketSelector_create,\
    (void *(*)(void *))sfSocketSelector_destroy)
#define my_sf_free() my_sfalloc(NULL, NULL)

    #include "infos.h"
    #include "dungeon.h"
    #include "atlas.h"
    #include "entity.h"
    #include "inputs.h"
    #include "my.h"
    #include "math.h"
    #include "printf.h"
    #include "items.h"
    #include "types.h"
    #include "dialog.h"
    #define APPEND -1

typedef struct map_info map_inf;

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
    QUIZ
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
    OTHERS,
    IG_OPTIONS,
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
    OTHERS_IDX,
    IG_OPTIONS_IDX,
    PAUSE_DG_IDX,
}menu_indx;

typedef enum language {
    DEFAULT = -1,
    ENGLISH,
    FRANCAIS,
}language;

typedef struct cpp_garbage {
    void *data;
    void *(*create)(void);
    void *(*destroy)(void *);
} cpp_garbage;

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

typedef struct inventory_t {
    struct inventory_slot **slots;
    int size;
} inventory;

typedef struct player_t {
    int offset;
    enum direction_t direction;
    float speed;
    int *slist;
    int **rlist;
    sfIntRect r;
    sfVector2i limit;
    float animc;
    int shiny;
    sfSprite *test;
    sfVector2f vel;
    sfVector2f sentpos;
    float time;
    sfVector2f nextpos;
    struct inventory_t *inv;
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
    struct player_t *p;
    sfVector2f target;
    sfIpAddress ip;
    int cscene;
    int port;
    int connected;
} other;

typedef struct dungeon_t {
    sfImage *img;
    struct map_info *inf;
    int in;
    list *enemies;
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
    int *volumes;
    int c_fps;
    sfClock *play_time;
    const char **fps;
    const char **key_list;
    dline *playtime;
    dline *ig_choices[3];
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
    struct menus *others_menu;
    struct menus *ig_options_menu;
    struct menus *options_menu;
    struct menus *current_menu;
    sfRenderStates state;
    struct settings_t *settings;
    struct intro_assets_t *intro;
    struct ditto_assets_t *ditto;
    struct dream_assets_t *dream;
    struct quiz_t *quiz;
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
    struct player_t *pla;
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
} date_t;

typedef struct inventory_slot {
    struct dialog_line_t *line;
    int id;
    void (*use)(wininf *, struct inventory_slot **);
} invslot;

void use_apple(wininf *inf, invslot **slot);

////////////////////////////////////////////////////////////
//Flags Handling
void manage_fps(char *arg, wininf *inf);
//Flags Handling
void manage_host(char *arg, wininf *inf);
//Flags Handling
void manage_lang(char *arg, wininf *inf);
//Flags Handling
void manage_client(char *arg, wininf *inf);
//Flags Handling
void change_settings(int opt, char *arg, wininf *inf);
//Flags Handling
int get_settings_flags(int ac, char **av, wininf *win);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Dungeon Generation
void create_dungeon(wininf *win, char *name);
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
void *my_malloc(size_t size);
//Utility functions
void free_musics(wininf *inf);
//Utility functions
void my_free_array(char **array);
//Utility functions
void my_free_array(char **array);
//Utility functions
int get_int_len(long long int nbr);
//Utility functions
char *unix_to_date(long int seconds);
//Utility functions
void end_global_free(components *all);
//Utility functions
int pos_char(char *string, char *presence);
//Utility functions
char **my_strtwa(char const *str, char *limit);
//Utility functions
char *my_strdup_to_char(char *src, char *delim);
//Utility functions
void *my_memset(void *dest, int value, int length);
//Utility functions
void *my_sfalloc(void *(*create)(void), void *(*destroy)(void *));
//Utility functions
char *my_slice_array(int direction, char *strslice, int nbslice);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Dialogs Handling
sfIntRect find_icons(wininf *inf, char *str);
//Dialogs Handling
int treat_balise(char *balise, sfColor *color, wininf *inf);
//Dialogs Handling
dline *load_line(char *line, int size, wininf *inf, void *(ptr)(size_t t));
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
void draw_intro(wininf *inf);
//Drawing functions
void draw_dream(wininf *inf);
//Drawing functions
void draw_quiz(wininf *inf, player *p);
//Drawing functions
void draw_player(wininf *inf, player *p);
//Drawing functions
void draw_dungeon(wininf *inf, player *p);
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
void center_menu(menuss *menu, wininf *inf, player *p);
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
void init_fps(wininf *inf);
//Initializations
network *init_network(void);
//Initializations
void set_pokemon(wininf *inf);
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
sfRenderStates create_shiny_test(void);
//Initializations
player *init_player(wininf inf, int id);
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
void create_enemy(wininf *inf, dungeon *d, sfVector2i pos);
//Initializations
void place_decorations(char *line, sfImage *atlas, char **csv, list **l);
//Initializations
void create_static_anim(sfImage *atlas, char *name, list **l, char **csv);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Updates
void treat_axis(wininf *inf);
//Updates
void update_inputs(wininf *inf);
//Updates
void update_camera(wininf *inf);
//Updates
void update_time(wininf *infos);
//Updates
void update_keyboard(wininf *inf);
//Updates
void update_joysticks(wininf *inf);
//Updates
void update_mobs(wininf *inf, player *p);
//Updates
void update_events(wininf *inf, player *p);
//Updates
void update_enemy(player *enemy, wininf *inf, player *p);
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
void go_pause(wininf *inf);
//Menu pointers
void go_others(wininf *inf);
//Menu pointers
void go_keybinds(wininf *inf);
//Menu pointers
void go_ig_options(wininf *inf);
//Menu pointers
void left_main_vol(wininf *inf);
//Menu pointers
void left_main_fps(wininf *inf);
//Menu pointers
void change_volume(wininf *inf);
//Menu pointers
void right_main_vol(wininf *inf);
//Menu pointers
void right_main_fps(wininf *inf);
//Menu pointers
void change_keybind(wininf *inf);
//Menu pointers
void change_volume_ig(wininf *inf);
//Menu pointers
void init_load_pointers(wininf *inf);
//Menu pointers
void init_options_pointers(wininf *inf);
//Menu pointers
void init_main_menu_pointers(wininf *inf);
//Menu pointers
void left_fps(wininf *inf, int current, sfVector2f old_pos, sfIntRect r);
//Menu pointers
void right_fps(wininf *inf, int current, sfVector2f old_pos, sfIntRect r);
//Menu pointers
void left_volume(wininf *inf, int current, sfVector2f old_pos, sfIntRect r);
//Menu pointers
void right_volume(wininf *inf, int current, sfVector2f old_pos, sfIntRect r);
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
int is_valid(list *c, sfFloatRect *r, wininf *inf, player *p);
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

////////////////////////////////////////////////////////////
//Movement
sfIntRect move_rect_player(player p);
//Movement
void perform_free_movement(wininf *inf, player *p);
//Movement
void perform_dungeon_movement(wininf *inf, player *p);
//Movement
void move_in_tunnel(player *e, wininf *inf, player *p);
//Movement
void player_direction_management(wininf *inf, player *p);
////////////////////////////////////////////////////////////




#endif
