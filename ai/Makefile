##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## do something apparently
##

SRC			=	$(shell find . -name "*.c" -type f)

OBJ			=	$(SRC:.c=.o)

NAME		=	zappy_ai

FLAG		=	-W -Wall -Wextra -g

CFLAGS	+=	$(FLAG)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(FLAG)

all:		$(NAME)
	cp $(NAME) ../

clean:
	rm -f $(OBJ)

fclean: 	clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re:    		fclean all
