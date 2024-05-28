/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Inventory
*/

#include "../../include/server.h"

static void send_inventory(server_t *server, int i)
{
    dprintf(FD_CLIENT, "[");
    dprintf(FD_CLIENT, "food %d,", PLAYER->food);
    dprintf(FD_CLIENT, " deraumere %d,", PLAYER->deraumere);
    dprintf(FD_CLIENT, " linemate %d,", PLAYER->linemate);
    dprintf(FD_CLIENT, " mendiane %d,", PLAYER->mendiane);
    dprintf(FD_CLIENT, " phiras %d,", PLAYER->phiras);
    dprintf(FD_CLIENT, " sibur %d,", PLAYER->sibur);
    dprintf(FD_CLIENT, " thystame %d", PLAYER->thystame);
    dprintf(FD_CLIENT, "]\n");
}

void inventory(server_t *server, int i, char *input)
{
    (void) input;
    if (PLAYER != NULL)
        send_inventory(server, i);
}
