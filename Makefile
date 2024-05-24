##
## EPITECH PROJECT, 2024
## server
## File description:
## Makefile
##

all:
	make -C ./server/ all
	make -C ./gui/ all
	make -C ./ai/ all

clean:
	make -C ./server/ clean
	make -C ./gui/ clean
	make -C ./ai/ clean
	rm -rf vgcore.*

fclean:
	make -C ./server/ fclean
	make -C ./gui/ fclean
	make -C ./ai/ fclean

re:    		fclean all
