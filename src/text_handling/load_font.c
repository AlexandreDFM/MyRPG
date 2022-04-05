/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** load_font
*/

#include "rpg.h"

int length_of_int(int a)
{
	int res = 0;
	for (; a && a != 1; res++, a /= 10);
	return res;
}

void load_alphabet(sfFont *font, int size)
{
	for (int i = 0; i < 26; i++) {
		sfFont_getGlyph(font, 'a' + i, size, sfFalse, 0.0f);
	}
	for (int i = 0; i < 26; i++) {
		sfFont_getGlyph(font, 'A' + i, size, sfFalse, 0.0f);
	}
}

void treat_balise(char *balise, sfColor *color)
{
	int r = my_atoi(balise);
	int g = my_atoi(balise + length_of_int(r) + 1);
	int b = my_atoi(balise + length_of_int(g) + 2 + length_of_int(r));
	if (balise[0] >= '0' && balise[0] <= '9') {
		*color = sfColor_fromRGB(r,g,b);
	}
	if (balise[0] == '/') {
		if (balise[1] == 'c') *color = sfWhite;
	}
}
