/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_textbox
*/

#include "rpg.h"

void init_textbox(wininf *win)
{
    sfIntRect r = (sfIntRect) {1232, 812, 224, 40};
    win->ui.background = atlas_to_sprite(r, win->atlases.atlas);
    sfVector2f mid = (sfVector2f) {r.width / 2, r.height / 2};
    sfSprite_setOrigin(win->ui.background, mid);
    win->ui.font = sfFont_createFromFile("fontt.ttf");
    win->ui.dialog = 0;
    win->ui.text_delay = 0.05f;
    load_alphabet(win->ui.font, FONT_SIZE);
}

dline *load_line(char *line, sfFont *font, int size, wininf *inf)
{
    int length = 0, posx = 0;
    int height = 0;
    char prev = 0;
    sfImage *font_alpha = sfTexture_copyToImage(sfFont_getTexture(font, size));
    int len = 0;
    int cond = 0;
    for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++, len++) {
        if (line[i] == '<') {
            cond = line[i] != '>' && line[i] != '\0' && line[i] != '\n';
            for (int y = i; cond; y++, i++) {
                cond = line[y] != '>' && line[y] != '\0' && line[y] != '\n';
            }
            if (line[i + 1] == 'i' && line[i + 2] == '_') len++;
                length += 8;
            continue;
        }
        sfGlyph glyph = sfFont_getGlyph(font, line[i], size, sfFalse, 0.0f);
        length += (int)glyph.advance;
        int yoffset = (glyph.textureRect.height + glyph.bounds.top);
        int nh = glyph.textureRect.height + yoffset;
        height = nh > height ? nh + 1 : height;
        if (prev) {
            length -= sfFont_getKerning(font, prev, line[i], size);
        }
        prev = line[i];
    }
    prev = 0;
    sfColor current_color = sfWhite;
    sfColor bl = sfColor_fromRGBA(0, 0, 0, 0);
    sfImage *img = sfImage_createFromColor(length, height, bl);
    int *steps = malloc(sizeof(int) * (len + 1));
    int li = 0;
    for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++, li++) {
        if (line[i] == '<') {
            int y = 0;
            for (; line[i + y] != '>'; y++);
            char test[y + 1];
            my_strncpy(test,line + i + 1, y - 1);
            test[y - 1] = '\0';
            int res = treat_balise(test, &current_color, inf);
            i += y;
            if (!res) {
                li--;
            } else {
                sfIntRect r = find_icons(inf, 2 + test);
                sfVector2i pos = (sfVector2i){posx - 1, 1};
                add_icon(pos, img, r, inf->atlases.atlas);
                posx += res;
                steps[li] = posx;
            }
            continue;
        }
        sfGlyph glyph = sfFont_getGlyph(font, line[i], size, sfFalse, 0.0f);
        int startY = (height - 1) + glyph.bounds.top;
        for (int y = 0; y < glyph.textureRect.height; y++) {
            for (int x = 0; x < glyph.textureRect.width; x++) {
                int gx = glyph.textureRect.left + x;
                int gy = glyph.textureRect.top + y;
                sfColor c = sfImage_getPixel(font_alpha, gx, gy);
                c = sfColor_modulate(c, current_color);
                sfImage_setPixel(img, x + posx, y + startY, c);
            }
        }
        posx += (int)glyph.advance;
        if (prev) {
            posx -= sfFont_getKerning(font, prev, line[i], size);
        }
        prev = line[i];
        steps[li] = posx;
    }
    dline *nl = malloc(sizeof(dline));
    nl->img = sfTexture_createFromImage(img, NULL);
    nl->sp = sfSprite_create();
    sfSprite_setTexture(nl->sp, nl->img, sfFalse);
    nl->steps = steps;
    nl->max = li - 1;
    nl->height = height;
    nl->i = 1;
    nl->time = 0;
    sfImage_destroy(font_alpha);
    sfImage_destroy(img);
    return nl;
}
