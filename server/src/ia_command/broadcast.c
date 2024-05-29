/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Broadcast
*/

#include "../../include/server.h"

void broadcast(server_t *server, int i, char *input)
{
    char **tab = get_parameters(input);

    (void) server;
    (void) i;
    free_tab(tab);
}
