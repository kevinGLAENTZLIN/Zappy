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
    client_t *client = CLIENT;

    (void) input;
    if (client->player != NULL) {
        tmp = get_team_by_name(server, client->player->team_name);
        if (tmp != NULL)
            send_client(client->fd, "%d\n", tmp->nb_max_player -
            tmp->nb_player);
    }
}
