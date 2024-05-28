/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Forward
*/

#include "../../include/server.h"

void forward(server_t *server, int i, char *input)
{
    (void) input;
    if (PLAYER != NULL) {
        if (PLAYER->direction == up)
            PLAYER->y = ((PLAYER->y - 1) + ZAPPY->y) % ZAPPY->y;
        if (PLAYER->direction == right)
            PLAYER->x = ((PLAYER->x + 1) + ZAPPY->x) % ZAPPY->x;
        if (PLAYER->direction == down)
            PLAYER->y = ((PLAYER->y + 1) + ZAPPY->y) % ZAPPY->y;
        if (PLAYER->direction == left)
            PLAYER->x = ((PLAYER->x - 1) + ZAPPY->x) % ZAPPY->x;
    }
}
