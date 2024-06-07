/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** msz
*/

#include "../../include/server.h"

/// @brief Msz command of the GUI protocol
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
void msz(server_t *server, int i, char *input)
{
    (void) input;
    send_client(FD_CLIENT, "msz %d %d\n", ZAPPY->x, ZAPPY->y);
}
