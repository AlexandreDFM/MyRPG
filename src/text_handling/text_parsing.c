/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** text_parsing
*/

#include "rpg.h"

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
    for (int i = 0; i < ln && line[i] != '\0' && line[i] != '\n'; i++,
    p->r.left++) {
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
