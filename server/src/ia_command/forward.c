/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Forward
*/

#include "../../include/server.h"

/// @brief Forward command of the Client protocol
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
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
        send_to_all_gui(server, "smg ppo #%d %d %d %d\n", player->id, player->x,
        player->y, player->direction + 1);
        client->time_to_wait = 7;
    }
}
