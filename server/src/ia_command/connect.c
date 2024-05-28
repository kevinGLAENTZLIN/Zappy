/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Connect
*/

#include "../../include/server.h"

void my_connect(server_t *server, int i, char *input)
{
    char **tab = get_parameters(input);

    (void) server;
    (void) i;
    free_tab(tab);
}
