/*
** EPITECH PROJECT, 2024
** server
** File description:
** player
*/

#include "../../include/server.h"

static int get_total_players(server_t *server)
{
    int count = 0;
    player_t *tmp = NULL;

    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        tmp = TEAM->players;
        while (tmp != NULL) {
            count += 1;
            tmp = tmp->next;
        }
    }
    return count;
}

void push_back_player(team_t *team, player_t *player, server_t *server)
{
    player_t *tmp = team->players;

    if (team->players == NULL)
        team->players = player;
    else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = player;
    }
    player->team_name = strdup(team->team_name);
    player->id = get_total_players(server);
    team->nb_player += 1;
}
