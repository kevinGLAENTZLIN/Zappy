/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Right
*/

#include "../../include/server.h"

void my_right(server_t *server, int i, char *input)
{
    (void) input;
    if (PLAYER != NULL) {
        PLAYER->direction = ((PLAYER->direction + 1) + 4) % 4;
        dprintf(FD_CLIENT, "ok\n");
    }
}