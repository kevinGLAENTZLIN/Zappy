/*
** EPITECH PROJECT, 2024
** server
** File description:
** player
*/

#include "../../include/server.h"

client_t *get_client_by_player(server_t *server, player_t *player)
{
    client_t *client = NULL;

    for (int i = 0; i < server->nb_client; i++) {
        client = CLIENT;
        if (strcmp(client->client_type, IA) == 0 && client->player == player)
            return client;
    }
    return NULL;
}

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

static void kill_player_loop(player_t *player, player_t *tmp)
{
    if (tmp->next != player)
        return;
    tmp->next = player->next;
    free_player(player);
    return;
}

void kill_player(server_t *server, player_t *player)
{
    player_t *tmp = NULL;

    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        tmp = TEAM->players;
        if (player == tmp) {
            TEAM->players = player->next;
            free_player(player);
            return;
        }
        while (tmp->next != NULL) {
            kill_player_loop(player, tmp);
            tmp = tmp->next;
        }
    }
}
