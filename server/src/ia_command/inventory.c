/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Inventory
*/

#include "../../include/server.h"

static void send_inventory(server_t *server, int i)
{
    client_t *client = CLIENT;

    send_client(client->fd, "[");
    send_client(client->fd, "food %d,", client->player->food);
    send_client(client->fd, " deraumere %d,", client->player->deraumere);
    send_client(client->fd, " linemate %d,", client->player->linemate);
    send_client(client->fd, " mendiane %d,", client->player->mendiane);
    send_client(client->fd, " phiras %d,", client->player->phiras);
    send_client(client->fd, " sibur %d,", client->player->sibur);
    send_client(client->fd, " thystame %d", client->player->thystame);
    send_client(client->fd, "]\n");
    client->time_to_wait = 1;
}

void inventory(server_t *server, int i, char *input)
{
    (void) input;
    if (PLAYER != NULL)
        send_inventory(server, i);
}
