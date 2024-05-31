/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** plv
*/

#include "../../include/server.h"

static void get_player_lvl(server_t *server, int i, int id, player_t *player)
{
    while (player != NULL) {
        if (player->id == id)
            dprintf(FD_CLIENT, "plv #%d %d\n", player->id, player->level + 1);
        player = player->next;
    }
}

void plv(server_t *server, int i, char *input)
{
    char **tab = get_parameters(input);

    if (tab == NULL || tab[0] == NULL || tab[1] == NULL ||
        tab[1][0] != '#' || is_number(&tab[1][0])) {
        free_tab(tab);
        return (void)dprintf(FD_CLIENT, "sbp\n");
    }
    for (int j = 0; ZAPPY->teams_name[j] != NULL; j++)
        get_player_lvl(server, i, atoi(&tab[1][0]), ZAPPY->teams[j]->players);
    free_tab(tab);
}
