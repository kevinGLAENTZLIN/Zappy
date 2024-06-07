/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** bct
*/

#include "../../include/server.h"

/// @brief Print to the GUI client the info of the Tile
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param tile Tile of the map to analyze
void display_tile_info(server_t *server, int i, tile_t *tile)
{
    int fd = FD_CLIENT;

    if (tile == NULL)
        return (void)send_client(fd, "sbp\n");
    send_client(fd, "bct %d %d", tile->x, tile->y);
    send_client(fd, " %d %d", tile->food, tile->linemate);
    send_client(fd, " %d %d", tile->deraumere, tile->sibur);
    send_client(fd, " %d %d", tile->mendiane, tile->phiras);
    send_client(fd, " %d\n", tile->thystame);
}

/// @brief Bct command of the GUI protocol
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
void bct(server_t *server, int i, char *input)
{
    char **tab = get_parameters(input);
    int x = 0;
    int y = 0;

    if (tab == NULL || tab[0] == NULL || !is_number(tab[1]) ||
        !is_number(tab[2])) {
        free_tab(tab);
        return (void)send_client(FD_CLIENT, "sbp\n");
    }
    x = atoi(tab[1]);
    y = atoi(tab[2]);
    if (x >= ZAPPY->x || x < 0 || y >= ZAPPY->y || y < 0) {
        free_tab(tab);
        return (void)send_client(FD_CLIENT, "sbp\n");
    }
    display_tile_info(server, i, MAP[y][x]);
    free_tab(tab);
}
