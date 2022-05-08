##
## EPITECH PROJECT, 2022
## scrapper
## File description:
## generate_spritesheet
##

from distutils.command.build import build
from PIL import Image
import os.path

im = Image.open("convert.png")
im = im.convert('RGB')
r, g, b = im.getpixel((1, 1))
color = (r, g, b, 255)

CELL_SIZE = 24

if (os.path.isfile("result.png")):
	os.remove("result.png")
img = Image.new('RGB', (24 * 6, 24 * 47), color = 'red')
jumping = [(0, 0), (0, 1), (0, 2), (1, 0), (1, 1), (1, 2), (2, 0), (2, 1), (2, 2), (3, 0), (3, 1), (3, 2), (4, 0), (4, 1), (5, 0), (5, 2), (6, 1), (7, 0), (7, 1), (7, 2), (8, 1), (9, 1), (10, 0), (10, 2), (11, 1), (12, 1), (13, 0), (13, 2), (14, 1), (15, 0), (15, 1), (16, 0), (16, 1), (17, 0), (17, 1), (18, 0), (18, 1), (19, 0), (19, 1), (20, 0), (20, 1), (21, 0), (21, 1), (22, 0), (22, 1), (23, 0), (23, 1)]


def build_line(where, start):
	to_save = 0
	for i in range(24):
		for y in range(3):
			truc = start[1] + i * 25
			machin = start[0]
			region = im.crop((machin + y * 25, truc,machin + y * 25 + CELL_SIZE, truc + CELL_SIZE))
			region = region.convert('RGB')
			if (i, y) in jumping:
				w, x, c = region.getpixel((0,0))
				if ((w,x,c,255) != color):
					img.paste(region, (where,to_save, where + CELL_SIZE, to_save + CELL_SIZE))
				to_save += 24


build_line(0, (84, 163))
build_line(24, (84, 163))
build_line(48, (84, 163))

build_line(72, (309, 163))
build_line(96, (309, 163))
build_line(96, (309+75, 163))
build_line(120, (309, 163))

build_line(24, (159, 163))
build_line(48, (234, 163))

img.save("result.png")