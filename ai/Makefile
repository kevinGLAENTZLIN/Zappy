##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## do something apparently
##

SRC			=	$(shell find . -name "*.cpp" -type f)

OBJ			=	$(SRC:.cpp=.o)

NAME		=	zappy_ai

FLAGS		=	-std=c++20 -W -Wall -Wextra -g

CXXFLAGS	+=	$(FLAGS)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(FLAGS)

all:		$(NAME)
	cp $(NAME) ../

clean:
	rm -f $(OBJ)

fclean: 	clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re:    		fclean all
