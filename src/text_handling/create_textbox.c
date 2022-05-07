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

void parse_line(char *line, sfFont *f, sfIntRect *r)
{
    int ln = my_strlen(line); char prev = 0;
    for (int i = 0; i < ln && line[i] != '\0' && line[i] != '\n'; i++, r->left++) {
        if (line[i] == '\\' && line[i + 1] == 'n') {
            i++;
            r->top++;
            continue;
        }
        if (line[i] == '<') {
            int cond = line[i] != '>' && line[i] != '\0' && line[i] != '\n';
            for (int y = i; cond; y++, i++) {
                cond = line[y] != '>' && line[y] != '\0' && line[y] != '\n';
            }
            if (i < ln && line[i + 1] == 'i' && line[i + 2] == '_') r->left++;
                r->width += 8;
            continue;
        }
        sfGlyph glyph = sfFont_getGlyph(f, line[i], FONT_SIZE, sfFalse, 0.0f);
        r->width += (int)glyph.advance;
        int yoffset = (glyph.textureRect.height + glyph.bounds.top);
        int nh = glyph.textureRect.height + yoffset;
        r->height = nh > r->height ? nh + 1 : r->height;
        if (prev) {
            r->width -= sfFont_getKerning(f, prev, line[i], FONT_SIZE);
        }
        prev = line[i];
    }
}

int treat_parsing_balise(char *line, int *i, sfColor *ccol, wininf *inf, sfImage *img, int *li, sfIntRect *ref, int c_height, int *steps)
{
    int y = 0;
    for (; line[*i + y] != '>'; y++);
    char test[y + 1];
    my_strncpy(test,line + *i + 1, y - 1);
    test[y - 1] = '\0';
    int res = treat_balise(test, ccol, inf);
    *i = *i + y;
    if (!res) {
        *li = *li - 1;
    } else {
        sfIntRect r = find_icons(inf, 2 + test);
        sfVector2i pos = (sfVector2i){ref->width - 1, c_height + 3};
        add_icon(pos, img, r, inf->atlases.atlas);
        ref->width = ref->width + res;
        steps[*li] = ref->width;
    }
    return 1;
}

// len, nb_y, length, height
dline *load_line(char *line, int size, wininf *inf, void *(ptr)(size_t t))
{
    sfFont *f = inf->ui.font; char prev = 0;
    sfIntRect r = (sfIntRect) {0, 1, 0, 0}; parse_line(line, f, &r);
    sfImage *font_alpha = sfTexture_copyToImage(sfFont_getTexture(f, size));
    sfColor current_color = sfWhite;
    sfColor bl = sfColor_fromRGBA(0, 0, 0, 0);
    sfImage *img = sfImage_createFromColor(r.width, r.height * r.top + 2, bl);
    int *steps = ptr(sizeof(int) * (r.left + 1));
    int li = 0, c_height = 0;
    sfIntRect r2 = (sfIntRect) {0, li, 0, c_height}; //I, li, posx, height
    for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++, li++) {
        if (line[i] == '<' && treat_parsing_balise(line, &i, &current_color, inf, img, &li, &r2, c_height, steps)) continue;
        if (line[i] == '\\' && line[i + 1] == 'n') {
            i += 1;
            r2.width = 0; c_height += r.height;
            li--;
            continue;
        }
        sfGlyph glyph = sfFont_getGlyph(f, line[i], size, sfFalse, 0.0f);
        int startY = (r.height - 1) + glyph.bounds.top + c_height;
        for (int y = 0; y < glyph.textureRect.height; y++) {
            for (int x = 0; x < glyph.textureRect.width; x++) {
                int gx = glyph.textureRect.left + x;
                int gy = glyph.textureRect.top + y;
                sfColor c = sfImage_getPixel(font_alpha, gx, gy);
                c = sfColor_modulate(c, current_color);
                sfImage_setPixel(img, x + r2.width, y + startY, c);
            }
        }
        r2.width += (int)glyph.advance;
        if (prev) {
            r2.width -= sfFont_getKerning(f, prev, line[i], size);
        }
        prev = line[i];
        steps[li] = r2.width;
    } sfImage_destroy(font_alpha);
    return create_line_struct((dline_creator){img, steps, ptr}, r, li);
}

dline *create_line_struct(dline_creator dlcreator, sfIntRect r, int li)
{
    dline *nl = dlcreator.ptr(sizeof(dline));
    nl->img = sfTexture_createFromImage(dlcreator.img, NULL);
    nl->cline = 0;
    nl->sps = dlcreator.ptr(sizeof(sfSprite *) * r.top);
    for (int i = 0; i < r.top; i++) {
        nl->sps[i] = sfSprite_create();
        sfSprite *sp = nl->sps[i];
        float ch = r.height * i;
        sfSprite_setTexture(sp, nl->img, sfFalse);
        sfSprite_setTextureRect(sp, (sfIntRect){0, ch, 0, r.height});
    }
    nl->nblines = r.top; nl->steps = dlcreator.steps;
    nl->max = li - 1;
    nl->height = r.height;
    nl->i = 1;
    nl->time = 0;
    sfImage_destroy(dlcreator.img);
    return nl;
}
