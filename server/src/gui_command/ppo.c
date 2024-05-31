/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** ppo
*/

#include "../../include/server.h"

static void get_player_pos(server_t *server, int i, int id, player_t *player)
{
    while (player != NULL) {
        if (player->id == id)
            dprintf(FD_CLIENT, "ppo #%d %d %d %d\n", player->id, player->x,
            player->y, player->direction + 1);
        player = player->next;
    }
}

void ppo(server_t *server, int i, char *input)
{
    char **tab = get_parameters(input);

    if (tab == NULL || tab[0] == NULL || tab[1] == NULL ||
        tab[1][0] != '#' || is_number(&tab[1][0])) {
        free_tab(tab);
        return (void)dprintf(FD_CLIENT, "sbp\n");
    }
    for (int j = 0; ZAPPY->teams_name[j] != NULL; j++)
        get_player_pos(server, i, atoi(&tab[1][0]), ZAPPY->teams[j]->players);
    free_tab(tab);
}
