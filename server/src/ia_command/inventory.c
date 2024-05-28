/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Inventory
*/

#include "../../include/server.h"

void inventory(server_t *server, int i, char *input)
{
    char **tab = get_parameters(input);

    (void) server;
    (void) i;
    free_tab(tab);
}
