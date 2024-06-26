/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** sgt
*/

#include "../../include/server.h"

/// @brief Sgt command of the GUI protocol
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
void sgt(server_t *server, int i, char *input)
{
    (void) input;
    send_client(FD_CLIENT, "sgt %d\n", ZAPPY->frequence);
}
