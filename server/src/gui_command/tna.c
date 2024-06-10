/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** tna
*/

#include "../../include/server.h"

/// @brief Tna command of the GUI protocol
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
void tna(server_t *server, int i, char *input)
{
    (void) input;
    for (int j = 0; ZAPPY->teams_name[j] != NULL; j++)
        send_client(FD_CLIENT, "tna \"%s\"\n", ZAPPY->teams_name[j]);
}
