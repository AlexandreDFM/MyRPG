##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## file making
##
Reset = "\033[0m"
Black = "\033[0;30m"
Red = "\033[0;31m"
Green = "\033[0;32m"
Yellow = "\033[0;33m"
Blue = "\033[0;34m"
Purple = "\033[0;35m"
Cyan = "\033[0;36m"
White = "\033[0;37m"

NAME	= 	my_rpg

CC		=	gcc

RM		= rm -f

LIB		=  -L ./lib/my/ -lmy

SRC		= 	main.c											\
			src/create_components.c							\
			src/scene_handling/scene_handler.c				\
			src/window/init_window.c						\
			src/entity/draw_entity.c						\
			src/window/time_handling.c						\
			src/inputs/inputs.c								\
			src/events/events.c								\
			src/csv/load_csv.c								\
			src/texture_atlas/create_sprite_from_atlas.c	\
			src/texture_atlas/init_atlases.c				\
			src/utils/my_strtwa.c							\
			src/utils/lists/push_front.c					\
			src/utils/is_same.c								\
			src/utils/my_memset.c							\
			src/utils/lists/draw_list.c						\
			src/utils/lists/init_double.c					\
			src/entity/init_entity.c						\
			src/scene_handling/draw_home.c					\
			src/maths/pingpong.c							\
			src/maths/my_lerp.c								\
			src/maths/simple_maths.c						\
			src/maths/vector_maths.c						\
			src/anim/create_static_anim.c					\
			src/anim/handle_decorations.c					\
			src/player/init_player.c						\
			src/player/player_update.c						\
			src/camera/camera_follow.c						\
			src/camera/init_camera.c						\
			src/collisions/add_collisions.c					\
			src/collisions/collision_check.c				\
			src/collisions/draw_collisions.c				\
			src/collisions/init_triggers.c					\
			src/window/handle_transitions.c					\
			src/scene_handling/draw_scene.c					\
			src/pnjs/add_pnjs.c								\
			src/text_handling/create_textbox.c				\
			src/text_handling/load_font.c					\
			src/text_handling/icons_handler.c				\
			src/text_handling/init_text.c					\
			src/text_handling/create_dialog_list.c			\
			src/textbox/generate_textbox.c					\
			src/menu/draw_menu.c							\
			src/menu/draw_choices.c							\
			src/menu/move_cursor.c							\
			src/menu/init_menus_pointers.c					\
			src/menu/function_pointers/main_menu.c			\
			src/menu/function_pointers/load_menu_pointers.c	\
			src/menu/set_cursor.c							\
			src/menu/init_all_menus.c						\
			src/dungeon/edge_detection.c					\
			src/dungeon/map_generator.c						\
			src/settings/flags_handling.c					\
			src/network/connecting_utils.c					\
			src/network/network_syncing.c					\
			src/network/update_network.c					\
			src/network/handle_orders.c						\
			src/settings/init_settings.c					\



OBJ    = $(SRC:.c=.o)

CFLAGS += -Wall -pedantic -I./include -g3

LIBFLAG    = -I ./include -g3 -lGL -lcsfml-graphics					\
-lcsfml-window -lcsfml-system -lcsfml-audio -lcsfml-network 		\
-L ./lib/ -lmy														\

all:  $(OBJ) compile


compile:
	@make -C ./lib/my
	@$(CC) $(SRC) -o $(NAME) $(LIBFLAG) -lm
	@./bonus/pokeball.sh

clean:
	@$(RM) $(OBJ)
	@make -C ./lib/my fclean

fclean:
	@$(RM) $(NAME)
	@$(RM) $(OBJ)

re: fclean all
