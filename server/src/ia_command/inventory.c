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

    dprintf(client->fd, "[");
    dprintf(client->fd, "food %d,", client->player->food);
    dprintf(client->fd, " deraumere %d,", client->player->deraumere);
    dprintf(client->fd, " linemate %d,", client->player->linemate);
    dprintf(client->fd, " mendiane %d,", client->player->mendiane);
    dprintf(client->fd, " phiras %d,", client->player->phiras);
    dprintf(client->fd, " sibur %d,", client->player->sibur);
    dprintf(client->fd, " thystame %d", client->player->thystame);
    dprintf(client->fd, "]\n");
    client->time_to_wait = 1;
}

void inventory(server_t *server, int i, char *input)
{
    (void) input;
    if (PLAYER != NULL)
        send_inventory(server, i);
}
