/*
** EPITECH PROJECT, 2024
** server
** File description:
** player
*/

#include "../../include/server.h"

void push_back_player(team_t *team, player_t *player)
{
    player_t *tmp = team->players;

    if (team->players == NULL) {
        team->players = player;
    } else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = player;
    }
    player->id = team->nb_player;
    team->nb_player += 1;
}

player_t *get_player_by_client(server_t *server, int i)
{
    team_t *tmp = get_team_by_name(server, CLIENT->team_name);
    player_t *player = NULL;

    if (tmp == NULL)
        return NULL;
    player = tmp->players;
    while (player != NULL) {
        if (player->id == CLIENT->player_id)
            return player;
        player = player->next;
    }
    return player;
}
