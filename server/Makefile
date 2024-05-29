##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Make pizza_server binary
##

SRC			=	$(shell find . -name "*.c" -type f)

OBJ			=	$(SRC:.c=.o)

NAME		=	zappy_server

FLAG		=	-I../include -W -Wall -Wextra -g

CFLAGS	+=	$(FLAG)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(FLAG)
	cp $(NAME) ../

all:		$(NAME)

clean:
	rm -f $(OBJ)

fclean: 	clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re:    		fclean all
