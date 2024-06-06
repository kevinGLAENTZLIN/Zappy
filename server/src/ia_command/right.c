/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Right
*/

#include "../../include/server.h"

void my_right(server_t *server, int i, char *input)
{
    client_t *client = CLIENT;

    (void) input;
    if (client->player != NULL) {
        client->player->direction = ((client->player->direction + 1) + 4) % 4;
        send_client(client->fd, "ok\n");
        client->time_to_wait = 7;
    }
}
