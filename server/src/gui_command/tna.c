/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** tna
*/

#include "../../include/server.h"

void tna(server_t *server, int i, char *input)
{
    (void) input;
    for (int j = 0; ZAPPY->teams_name[j] != NULL; j++)
        send_client(FD_CLIENT, "tna \"%s\"\n", ZAPPY->teams_name[j]);
}
