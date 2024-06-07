/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Right
*/

#include "../../include/server.h"

/// @brief Right command of the Client protocol
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
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
