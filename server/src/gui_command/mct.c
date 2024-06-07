/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** mct
*/

#include "../../include/server.h"

/// @brief Mct command of the GUI protocol
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
void mct(server_t *server, int i, char *input)
{
    (void) input;
    for (int y = 0; y < ZAPPY->y; y++)
        for (int x = 0; x < ZAPPY->x; x++)
            display_tile_info(server, i, MAP[y][x]);
}
