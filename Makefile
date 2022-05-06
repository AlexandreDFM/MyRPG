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

SRC		= 	main.c												\
			src/window/create_components.c						\
			src/scene_handling/scene_handler.c					\
			src/window/init_window.c							\
			src/window/log_system.c								\
			src/window/shader/create_state.c					\
			src/entity/draw_entity.c							\
			src/window/time_handling.c							\
			src/inputs/inputs.c									\
			src/events/events.c									\
			src/csv/load_csv.c									\
			src/texture_atlas/create_sprite_from_atlas.c		\
			src/texture_atlas/init_atlases.c					\
			src/utils/my_strtwa.c								\
			src/utils/my_malloc.c								\
			src/utils/my_sfalloc.c								\
			src/utils/lists/push_front.c						\
			src/utils/my_itoa.c									\
			src/utils/is_same.c									\
			src/utils/my_atof.c									\
			src/utils/my_memset.c								\
			src/utils/get_arr_len.c								\
			src/utils/lists/draw_list.c							\
			src/utils/lists/init_double.c						\
			src/utils/unix_to_date.c							\
			src/utils/my_strdup_to_char.c						\
			src/utils/my_checks.c								\
			src/utils/my_slice_array.c							\
			src/scene_handling/draw_home.c						\
			src/maths/pingpong.c								\
			src/maths/my_lerp.c									\
			src/maths/simple_maths.c							\
			src/maths/vector_maths.c							\
			src/anim/create_static_anim.c						\
			src/anim/handle_decorations.c						\
			src/items/use_food.c								\
			src/player/init_player.c							\
			src/player/player_update.c							\
			src/player/player_inventory.c						\
			src/player/drop_item.c								\
			src/player/anims/move_rect.c						\
			src/player/anims/update_sprite.c					\
			src/camera/camera_follow.c							\
			src/camera/init_camera.c							\
			src/collisions/add_collisions.c						\
			src/collisions/collision_check.c					\
			src/collisions/draw_collisions.c					\
			src/collisions/init_triggers.c						\
			src/collisions/scene_triggers.c						\
			src/window/handle_transitions.c						\
			src/scene_handling/draw_scene.c						\
			src/pnjs/add_pnjs.c									\
			src/text_handling/create_textbox.c					\
			src/text_handling/load_font.c						\
			src/text_handling/icons_handler.c					\
			src/text_handling/init_text.c						\
			src/text_handling/create_dialog_list.c				\
			src/textbox/generate_textbox.c						\
			src/menu/draw_menu.c								\
			src/menu/draw_inv.c									\
			src/menu/draw_choices.c								\
			src/menu/move_cursor.c								\
			src/menu/init_menus_pointers.c						\
			src/menu/function_pointers/use_item.c				\
			src/menu/function_pointers/main_menu.c				\
			src/menu/function_pointers/options_goto.c			\
			src/menu/function_pointers/others_pointers.c		\
			src/menu/function_pointers/options_pointers.c		\
			src/menu/function_pointers/load_menu_pointers.c		\
			src/menu/function_pointers/options_pointers_fps.c	\
			src/menu/function_pointers/main_menu_play_option.c	\
			src/menu/function_pointers/options_pointers_volume.c\
			src/menu/set_cursor.c								\
			src/menu/center_menu.c								\
			src/menu/update_player_pokemon.c					\
			src/menu/init_all_menus.c							\
			src/menu/init_ig_menus.c							\
			src/menu/update_playtime.c							\
			src/dungeon/coordinate.c							\
			src/dungeon/dungeon_generation.c					\
			src/dungeon/edge_detection.c						\
			src/dungeon/draw_dungeons.c							\
			src/dungeon/map_generator.c							\
			src/dungeon/enemy/create_enemy.c					\
			src/dungeon/enemy/update_enemy.c					\
			src/settings/flags_handling.c						\
			src/settings/manage_flags.c							\
			src/network/connecting_utils.c						\
			src/network/network_syncing.c						\
			src/network/update_network.c						\
			src/network/handle_orders.c							\
			src/settings/init_settings.c						\
			src/intro/create_intro.c							\
			src/intro/intro.c									\
			src/intro/manage_intro.c							\
			src/intro/move_rect_intro.c							\
			src/intro/my_hsvtorgb.c								\
			src/intro/plan_intro.c								\
			src/intro/plan1_2_intro.c							\
			src/intro/plan3_4_intro.c							\
			src/intro/delete_intro.c							\
			src/ditto/create_ditto.c							\
			src/ditto/ditto.c									\
			src/ditto/delete_ditto.c							\
			src/dream/create_dream.c							\
			src/dream/dream.c									\
			src/dream/delete_dream.c							\
			src/free_memory/my_free_array.c						\
			src/cinematics_elements/create_cine_elements.c		\
			src/cinematics_elements/create_cine_elements_spe.c	\
			src/cinematics_elements/display_elements.c			\
			src/quiz/create_quiz.c								\
			src/quiz/quiz.c										\
			src/quiz/calculate_quiz.c							\
			src/quiz/delete_quiz.c								\
			src/quiz/create_questions_quiz.c					\
			src/quiz/move_cursor_quiz.c							\
			src/quiz/handle_quiz.c								\
			src/quiz/quiz_choice.c								\
			src/sounds/init_sounds.c							\



OBJ    = $(SRC:.c=.o)

CFLAGS += -Wall -pedantic -I./include -g3

LIBFLAG    = -I ./include -g3 -lGL -lcsfml-graphics					\
-lcsfml-window -lcsfml-system -lcsfml-audio -lcsfml-network 		\
-L ./lib/ -lmy														\

all:  $(OBJ) compile


compile:
	@make -C ./lib/my
	@$(CC) $(SRC) -o $(NAME) $(LIBFLAG) -lm
	## @./bonus/pokeball.sh

clean:
	@$(RM) $(OBJ)
	@make -C ./lib/my fclean

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(OBJ)

re: fclean all
