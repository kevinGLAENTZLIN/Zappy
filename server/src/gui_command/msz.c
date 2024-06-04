/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** msz
*/

#include "../../include/server.h"

void msz(server_t *server, int i, char *input)
{
    (void) input;
    send_client(FD_CLIENT, "msz %d %d\n", ZAPPY->x, ZAPPY->y);
}
