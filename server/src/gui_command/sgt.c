/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** sgt
*/

#include "../../include/server.h"

void sgt(server_t *server, int i, char *input)
{
    (void) input;
    send_client(FD_CLIENT, "sgt %d\n", ZAPPY->ticks);
}
