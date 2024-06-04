/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Forward
*/

#include "../../include/server.h"

void forward(server_t *server, int i, char *input)
{
    client_t *client = CLIENT;
    player_t *player = client->player;

    (void) input;
    if (player != NULL) {
        if (player->direction == up)
            player->y = ((player->y - 1) + ZAPPY->y) % ZAPPY->y;
        if (player->direction == right)
            player->x = ((player->x + 1) + ZAPPY->x) % ZAPPY->x;
        if (player->direction == down)
            player->y = ((player->y + 1) + ZAPPY->y) % ZAPPY->y;
        if (player->direction == left)
            player->x = ((player->x - 1) + ZAPPY->x) % ZAPPY->x;
        send_client(client->fd, "ok\n");
        client->time_to_wait = 7;
    }
}
