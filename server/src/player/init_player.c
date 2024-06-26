/*
** EPITECH PROJECT, 2024
** server
** File description:
** player
*/

#include "../../include/server.h"

/// @brief Load a default inventory to the given player
/// @param player Player to set the inventory
static void load_player_inventory(player_t *player)
{
    player->food = 10;
    player->level = 0;
    player->linemate = 0;
    player->deraumere = 0;
    player->sibur = 0;
    player->mendiane = 0;
    player->phiras = 0;
    player->thystame = 0;
}

/// @brief Initialize a default player at the given coordinate
/// @param x Starting X coordinate of the player
/// @param y Starting Y coordinate of the player
/// @return NULL if any error found, else the initialized player
player_t *init_player(int x, int y)
{
    player_t *player = malloc(sizeof(player_t));

    if (player == NULL)
        return my_perror("init_player");
    srand(time(NULL));
    player->id = -1;
    player->x = x;
    player->y = y;
    player->team_name = NULL;
    player->next = NULL;
    player->direction = rand() % 4;
    load_player_inventory(player);
    return player;
}

/// @brief Free the given player
/// @param player Player to free
void free_player(player_t *player)
{
    if (player == NULL)
        return;
    if (player->team_name != NULL)
        free(player->team_name);
    free(player);
}

/// @brief Free all players of the given team
/// @param team Team to free all of its players
void free_players(team_t *team)
{
    player_t *tmp = NULL;

    if (team == NULL)
        return;
    tmp = team->players;
    if (tmp == NULL)
        return;
    team->players = tmp->next;
    free_players(team);
    free_player(tmp);
}
