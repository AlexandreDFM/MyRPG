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
    char *new_name = malloc(my_strlen(name[inf->lang]) + 1);
    my_strcpy(new_name, name[inf->lang]);
    my_strcat(new_name, ":");
    dline *tmp = load_line(new_name, inf->ui.font, 15, inf);
    list *tmp2 = inf->pause_menu->texts;
    while (tmp2->next->next != NULL) tmp2 = tmp2->next;
    sfVector2f pos = sfSprite_getPosition(tmp2->data);
    sfIntRect r; r.left = 0, r.top = 0;
    r.width = tmp->steps[tmp->max], r.height = tmp->height;
    sfSprite_setTextureRect(tmp->sp, r);
    tmp2->data = tmp->sp;
    sfSprite_setPosition(inf->pause_menu->texts->data, pos);
}
