/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** pin
*/

#include "../../include/server.h"

static void get_player_inv(server_t *server, int i, int id, player_t *player)
{
    while (player != NULL) {
        if (player->id == id)
            dprintf(FD_CLIENT, "pin #%d %d %d %d %d %d %d %d %d %d\n",
            player->id, player->x, player->y, player->food, player->linemate,
            player->deraumere, player->sibur, player->mendiane, player->phiras,
            player->thystame);
        player = player->next;
    }
}

void pin(server_t *server, int i, char *input)
{
    char **tab = get_parameters(input);

    if (tab == NULL || tab[0] == NULL || tab[1] == NULL ||
        tab[1][0] != '#' || is_number(&tab[1][1])) {
        free_tab(tab);
        return (void)dprintf(FD_CLIENT, "sbp\n");
    }
    for (int j = 0; ZAPPY->teams_name[j] != NULL; j++)
        get_player_inv(server, i, atoi(&tab[1][1]), ZAPPY->teams[j]->players);
    free_tab(tab);
}
