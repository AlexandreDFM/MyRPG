/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_cine_elements
*/

#include "rpg.h"
#include "cinematics_elements.h"

sfSprite *atlas_to_sprite_full(sfIntRect rect, sfImage *atlas)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = my_texture_from_image(atlas, NULL);
    sfSprite_setTexture(sprite, texture, sfFalse);
    return sprite;
}

sfIntRect csv_to_rect(char *linecsv, int idx)
{
    sfIntRect rect;
    char **linestw = my_strtwa(linecsv, ";\n");
    rect.left = my_atoi(linestw[idx]);
    rect.top = my_atoi(linestw[idx + 1]);
    rect.width = my_atoi(linestw[idx + 2]);
    rect.height = my_atoi(linestw[idx + 3]);
    my_free_array(linestw);
    return rect;
}

sfVector2f csv_to_vector2f(char *linecsv, int idx)
{
    sfVector2f pos;
    char **linestw = my_strtwa(linecsv, ";\n");
    pos.x = my_atof(linestw[idx]);
    pos.y = my_atof(linestw[idx + 1]);
    my_free_array(linestw);
    return pos;
}

cine_ele c_ele(sfImage *img, char *csv, int idx)
{
    cine_ele ele;
    char **csv2 = load_csv(csv);
    sfIntRect rectimage = csv_to_rect(csv2[idx], 1);
    sfIntRect rectsprite = csv_to_rect(csv2[idx], 5);
    sfVector2f possprite = csv_to_vector2f(csv2[idx], 9);
    sfVector2f sizesprite = csv_to_vector2f(csv2[idx], 11);
    ele.sprite = atlas_to_sprite(rectimage, img);
    ele.rect = rectsprite;
    ele.rimage = rectimage;
    ele.pos = possprite;
    ele.resize = sizesprite;
    sfSprite_setPosition(ele.sprite, ele.pos);
    sfSprite_setScale(ele.sprite, ele.resize);
    return ele;
}
