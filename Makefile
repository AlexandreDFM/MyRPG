##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## file making
##

NAME	= 	my_rpg

CC		=	gcc

RM		= rm -f

LIB		=  -L ./lib/my/ -lmy

SRC		= 	main.c									\
			src/scene_handling/scene_handler.c		\
			src/window/init_window.c				\
			src/inputs/inputs.c						\
			src/events/events.c						\
		

OBJ    = $(SRC:.c=.o)

CFLAGS += -Wall -pedantic -I./include -g3

LIBFLAG    = -I ./include -g3 -lcsfml-graphics	\
-lcsfml-window -lcsfml-system -lcsfml-audio		\

all: $(NAME)

$(NAME): $(OBJ)
	# @make -C ./lib/my
	@$(CC) $(SRC) -o $(NAME) $(LIBFLAG) -lm

clean:
	@$(RM) $(OBJ)
	@make -C ./lib/my fclean

fclean:
	@$(RM) $(NAME)
	@$(RM) $(OBJ)

re: fclean all
