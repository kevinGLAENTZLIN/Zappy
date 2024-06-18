##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Make pizza_server binary
##

SRC		=	./src/gui_command/mct.c\
			./src/gui_command/bct.c\
			./src/gui_command/msz.c\
			./src/gui_command/pin.c\
			./src/gui_command/plv.c\
			./src/gui_command/ppo.c\
			./src/gui_command/sgt.c\
			./src/gui_command/sst.c\
			./src/gui_command/tna.c\
			./src/ia_command/broadcast.c\
			./src/ia_command/connect.c\
			./src/ia_command/eject.c\
			./src/ia_command/fork.c\
			./src/ia_command/forward.c\
			./src/ia_command/incantation.c\
			./src/ia_command/inventory.c\
			./src/ia_command/left.c\
			./src/ia_command/look.c\
			./src/ia_command/right.c\
			./src/ia_command/set.c\
			./src/ia_command/take.c\
			./src/player/init_player.c\
			./src/player/player.c\
			./src/team/init_team.c\
			./src/team/team.c\
			./src/server/my_server.c\
			./src/server/set_server.c\
			./src/client.c\
			./src/command.c\
			./src/command_util.c\
			./src/command_vector.c\
			./src/egg.c\
			./src/game_condition.c\
			./src/gui_util.c\
			./src/main.c\
			./src/map.c\
			./src/tick.c\
			./src/signal.c\
			./src/zappy.c

BUFFER_SRC	=	./src/buffer.c

OBJ			=	$(SRC:.c=.o)

BUFFER_OBJ			=	$(BUFFER_SRC:.c=.o)

NAME		=	zappy_server

LIB_NAME	=	libbuffer.a

FLAG		=	-I../include -W -Wall -Wextra -g -lm

CFLAGS	+=	$(FLAG)

all:		$(NAME)

$(LIB_NAME):	$(BUFFER_OBJ)
	ar rc $(LIB_NAME) $(BUFFER_OBJ)

$(NAME):	$(LIB_NAME)\
			$(OBJ)
	gcc -o $(NAME) $(OBJ) $(FLAG) -L. -lbuffer
	cp $(NAME) ../

clean:
	rm -f $(OBJ)
	rm -f $(BUFFER_OBJ)

fclean: 	clean
	rm -f $(LIB_NAME)
	rm -f $(NAME)
	rm -f ../$(NAME)

re:    		fclean all

.PHONY:  all clean fclean re
