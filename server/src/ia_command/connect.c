/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Connect
*/

#include "../../include/server.h"

void my_connect(server_t *server, int i, char *input)
{
    team_t *tmp = NULL;

    (void) input;
    if (PLAYER != NULL) {
        tmp = get_team_by_name(server, PLAYER->team_name);
        if (tmp != NULL)
            dprintf(FD_CLIENT, "%d\n", tmp->nb_max_player - tmp->nb_player);
    }
}
