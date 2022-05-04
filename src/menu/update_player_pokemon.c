/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** update_player_pokemon
*/

#include "rpg.h"

void set_pokemon(wininf *inf)
{
    char **name =
    my_strtwa(inf->atlases.poke_names[inf->settings->pokemon], ";\n");
    char *new_name = my_malloc(my_strlen(name[inf->lang]) + 2);
    my_strcpy(new_name, name[inf->lang]);
    my_strcat(new_name, ":\0");
    dline *tmp = load_line(new_name, 15, inf, my_malloc);
    list *tmp2 = inf->pause_menu->texts;
    while (tmp2->next->next != NULL) tmp2 = tmp2->next;
    sfVector2f pos = sfSprite_getPosition(tmp2->data);
    sfIntRect r; r.left = 0, r.top = 0;
    r.width = tmp->steps[tmp->max], r.height = tmp->height;
    sfSprite_setTextureRect(tmp->sps[0], r);
    tmp2->data = tmp->sps[0];
    sfSprite_setPosition(inf->pause_menu->texts->data, pos);
    my_free_array(name);
}
