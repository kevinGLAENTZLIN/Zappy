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
}
