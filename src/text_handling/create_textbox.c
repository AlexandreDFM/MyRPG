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

int parse_balise(char *line, int i, int ln, dline_parsing *p)
{
    if (line[i] == '<') {
        int cond = line[i] != '>' && line[i] != '\0' && line[i] != '\n';
        for (int y = i; cond; y++, i++) {
            cond = line[y] != '>' && line[y] != '\0' && line[y] != '\n';
        }
        if (i < ln && line[i + 1] == 'i' && line[i + 2] == '_') p->r.left++;
            p->r.width += 8;
        return 1;
    }
    return 0;
}

void parse_line(char *line, sfFont *f, dline_parsing *p)
{
    int ln = my_strlen(line); char prev = 0;
    for (int i = 0; i < ln && line[i] != '\0' && line[i] != '\n'; i++, p->r.left++) {
        if (line[i] == '\\' && line[i + 1] == 'n') {
            i++;
            p->r.top++;
            continue;
        }
        if (parse_balise(line, i, ln, p)) continue;
        sfGlyph glyph = sfFont_getGlyph(f, line[i], FONT_SIZE, sfFalse, 0.0f);
        p->r.width += (int)glyph.advance;
        int yoffset = (glyph.textureRect.height + glyph.bounds.top);
        int nh = glyph.textureRect.height + yoffset;
        p->r.height = nh > p->r.height ? nh + 1 : p->r.height;
        if (prev) {
            p->r.width -= sfFont_getKerning(f, prev, line[i], FONT_SIZE);
        }
        prev = line[i];
    }
}

int treat_parsing_balise(char *line, dline_parsing *p, wininf *inf, int *steps)
{
    int y = 0;
    for (; line[p->r2.left + y] != '>'; y++);
    char test[y + 1];
    my_strncpy(test, line + p->r2.left + 1, y - 1);
    test[y - 1] = '\0';
    int res = treat_balise(test, &p->current_color, inf);
    p->r2.left = p->r2.left + y;
    if (!res) {
        p->r2.top = p->r2.top - 1;
    } else {
        sfIntRect r = find_icons(inf, 2 + test);
        sfVector2i pos = (sfVector2i){p->r2.width - 1, p->r2.height + 1};
        add_icon(pos, p->img, r, inf->atlases.atlas);
        p->r2.width = p->r2.width + res;
        steps[p->r2.top] = p->r2.width;
    }
    return 1;
}

void treat_letter_dialog(wininf *inf, char *line, dline_parsing *p, sfImage *font_alpha)
{
    sfGlyph glyph = sfFont_getGlyph(inf->ui.font, line[p->r2.left], FONT_SIZE, sfFalse, 0.0f);
    int startY = (p->r.height - 1) + glyph.bounds.top + p->r2.height;
    for (int y = 0; y < glyph.textureRect.height; y++) {
        for (int x = 0; x < glyph.textureRect.width; x++) {
            int gx = glyph.textureRect.left + x;
            int gy = glyph.textureRect.top + y;
            sfColor c = sfImage_getPixel(font_alpha, gx, gy);
            c = sfColor_modulate(c, p->current_color);
            sfImage_setPixel(p->img, x + p->r2.width, y + startY, c);
        }
    }
    p->r2.width += (int)glyph.advance;
}

dline_parsing *create_dline_help(sfFont *f, char *line)
{
    dline_parsing *p = malloc(sizeof(dline_parsing));
    sfIntRect r = (sfIntRect) {0, 1, 0, 0};
    p->r = r;
    p->r2 = (sfIntRect) {0, 0, 0, 0};
    p->current_color = sfWhite;
    parse_line(line, f, p);
    sfColor bl = sfColor_fromRGBA(0, 0, 0, 0);
    p->img = sfImage_createFromColor(p->r.width, p->r.height * p->r.top + 2,
        bl);
    return p;
}

int is_valid_dline(char *l, dline_parsing *p)
{
    return l[p->r2.left] != '\0' && l[p->r2.left] != '\n';
}

dline *load_line(char *l, int size, wininf *inf, void *(ptr)(size_t t))
{
    sfFont *f = inf->ui.font; char prev = 0;
    dline_parsing *p = create_dline_help(f, l);
    sfImage *font_alpha = sfTexture_copyToImage(sfFont_getTexture(f, size));
    int *steps = ptr(sizeof(int) * (p->r.left + 1));
    for (; is_valid_dline(l, p); p->r2.left++, p->r2.top++) {
        if (l[p->r2.left] == '<' && treat_parsing_balise(l, p, inf, steps))
            continue;
        if (l[p->r2.left] == '\\' && l[p->r2.left + 1] == 'n') {
            p->r2.left += 1; p->r2.width = 0; p->r2.height += p->r.height;
            p->r2.top--;
            continue;
        }
        treat_letter_dialog(inf, l, p, font_alpha);
        if (prev)
            p->r2.width -= sfFont_getKerning(f, prev, l[p->r2.left], size);
        prev = l[p->r2.left]; steps[p->r2.top] = p->r2.width;
    } sfImage_destroy(font_alpha);
    return create_lstruct((dl_creat){p->img, steps, ptr}, p->r, p->r2.top);
}

void update_rects_dialog(wininf *win)
{
    dline *c_line = (dline*)win->ui.dialog->data;
    if (c_line->i == c_line->max) {
        win->ui.dialog = win->ui.dialog->next;
        win->interacting = !win->ui.dialog ? 0 : win->interacting;
    } else {
        c_line->i = c_line->max - 1; c_line->cline = c_line->nblines - 1;
        for (int i = 0; i < c_line->nblines; i++) {
            sfSprite *sp = c_line->sps[i];
            sfTexture *t = (sfTexture *)sfSprite_getTexture(sp);
            sfVector2u si = sfTexture_getSize(t);
            sfSprite_setTextureRect(sp, (sfIntRect){0, c_line->height * i, si.x, c_line->height});
        }
    }
}

dline *create_lstruct(dl_creat dlcreator, sfIntRect r, int li)
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
