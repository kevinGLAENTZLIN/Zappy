/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Look
*/

#include "../../include/server.h"

void look(server_t *server, int i, char *input)
{
    char **tab = get_parameters(input);

    (void) server;
    (void) i;
    free_tab(tab);
}
