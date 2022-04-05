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
    sfSprite_setOrigin(win->ui.background, (sfVector2f) {r.width / 2, r.height / 2});
	win->ui.font = sfFont_createFromFile("fontt.ttf");
	win->ui.dialog = 0;
	load_alphabet(win->ui.font, FONT_SIZE);
}

dline *load_line(char *line, sfFont *font, int size)
{
	int length = 0, posx = 0;
	int height = size + 1;
	char prev = 0;
	sfImage *font_alpha = sfTexture_copyToImage(sfFont_getTexture(font, size));
	for (int i = 0; line[i] != '\0'; i++) {
		sfGlyph glyph = sfFont_getGlyph(font, line[i], size, sfFalse, 0.0f);
		length += (int)glyph.advance;
		height = glyph.textureRect.height > height ? glyph.textureRect.height : height;
		if (prev) {
			length -= sfFont_getKerning(font, prev, line[i], size);
		}
		prev = line[i];
	}
	prev = 0;
	sfColor current_color = sfWhite;
	sfImage *img = sfImage_createFromColor(length, height, sfColor_fromRGBA(0, 0, 0, 0));
	int *steps = malloc(sizeof(int) * (my_strlen(line) + 1));
	for (int i = 0, li = 0; line[i] != '\0'; i++, li++) {
		if (line[i] == '<') {
			int y = 0;
			for (; line[i + y] != '>'; y++);
			char test[y - 1];
			my_strncpy(test,line + i + 1, y - 1);
			treat_balise(test, &current_color);
			i += y;
			li--;
			continue;
		}
		sfGlyph glyph = sfFont_getGlyph(font, line[i], size, sfFalse, 0.0f);
		int startY = height - glyph.textureRect.height;
		for (int y = 0; y < glyph.textureRect.height; y++) {
			for (int x = 0; x < glyph.textureRect.width; x++) {
				sfColor col = sfImage_getPixel(font_alpha, glyph.textureRect.left + x, glyph.textureRect.top + y);
				col = sfColor_modulate(col, current_color);
				sfImage_setPixel(img, x + posx, y + startY, col);
			}
		}
		posx += (int)glyph.advance;
		if (prev) {
			posx -= sfFont_getKerning(font, prev, line[i], size);
		}
		prev = line[i];
		steps[li] = posx;
	}
	steps[my_strlen(line)] = 0;
	dline *nl = malloc(sizeof(dline));
	nl->img = sfTexture_createFromImage(img, NULL);
	nl->steps = steps;
	nl->height = height;
	nl->i = 0;
	nl->time = 0;
	return nl;
}
