##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## file making
##

NAME    = my_rpg

CC    = gcc

RM    = rm -f

SRC    = main.c								\

OBJ    = $(SRC:.c=.o)

CFLAGS += -Wall -pedantic -I./include -g3

LIBFLAG    = -L ./lib/my/ -lmy -I ./include -g3 -lcsfml-graphics 		\
-lcsfml-window -lcsfml-system -lcsfml-audio								\

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./lib/my
	@$(CC) $(SRC) -o $(NAME) $(LIBFLAG) -lm

clean:
	@$(RM) $(OBJ)
	@make -C ./lib/my fclean

fclean:
	@$(RM) $(NAME)
	@$(RM) $(OBJ)

re: fclean all
