/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** plv
*/

#include "../../include/server.h"

/// @brief Print to the GUI client the level of the Player
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param id ID of the player
/// @param player List of player
static void get_player_lvl(server_t *server, int i, int id, player_t *player)
{
    while (player != NULL) {
        if (player->id == id)
            send_client(FD_CLIENT, "plv #%d %d\n", player->id, player->level
            + 1);
        player = player->next;
    }
}

/// @brief Plv command of the GUI protocol
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
void plv(server_t *server, int i, char *input)
{
    char **tab = get_parameters(input);

    if (tab == NULL || tab[0] == NULL || tab[1] == NULL ||
        tab[1][0] != '#' || !is_number(&tab[1][1])) {
        free_tab(tab);
        return (void)send_client(FD_CLIENT, "sbp\n");
    }
    for (int j = 0; ZAPPY->teams_name[j] != NULL; j++)
        get_player_lvl(server, i, atoi(&tab[1][1]), ZAPPY->teams[j]->players);
    free_tab(tab);
}
