/*
** EPITECH PROJECT, 2024
** server
** File description:
** player
*/

#include "../../include/server.h"

/// @brief Get the client relative to the given player
/// @param server Structure that contains all games information
/// @return NULL if any error happened or if the Client has not been found
/// else the client
client_t *get_client_by_player(server_t *server, player_t *player)
{
    client_t *client = NULL;

    if (player == NULL || server == NULL)
        return NULL;
    for (int i = 0; i < server->nb_client; i++) {
        client = CLIENT;
        if (client->client_type != NULL && strcmp(client->client_type, IA) == 0
        && client->player == player)
            return client;
    }
    return NULL;
}

/// @brief Return the total amount of player in the whole server
/// @param server Structure that contains all games information
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

/// @brief Add the given player to the list of player of the given Team
/// @param server Structure that contains all games information
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
    if (player->team_name == NULL)
        return perror("push_back_player");
    player->id = get_total_players(server);
    team->nb_player += 1;
}

/// @brief Loop of kill_player function
/// @param player Player to kill
static void kill_player_loop(player_t *player, player_t *tmp)
{
    if (tmp->next != player)
        return;
    tmp->next = player->next;
    free_player(player);
    return;
}

/// @brief Kill the given player, remove it from his team and free it
/// @param server Structure that contains all games information
/// @param player Player to kill
void kill_player(server_t *server, player_t *player)
{
    player_t *tmp = NULL;

    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        tmp = TEAM->players;
        if (tmp == NULL)
            continue;
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
