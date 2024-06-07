/*
** EPITECH PROJECT, 2024
** server
** File description:
** team
*/

#include "../../include/server.h"

/// @brief Initialize a default team based on the given name
/// @param team_name Name of the team
/// @param nb_max Maximum number of client simulated connected
/// @return The initialized team
static team_t *init_team(char *team_name, int nb_max)
{
    team_t *team = malloc(sizeof(team_t));

    if (team == NULL)
        return (team_t *)my_perror("init_team");
    team->nb_max_player = nb_max;
    team->nb_player = 0;
    team->team_name = strdup(team_name);
    if (team->team_name == NULL) {
        free(team);
        return (team_t *)my_perror("init_team");
    }
    team->players = NULL;
    return team;
}

/// @brief Load each Team based on the teams name
/// @param zappy Structure that contains all games information
void load_zappy_teams(zappy_t *zappy)
{
    if (zappy == NULL)
        return;
    zappy->teams = malloc(sizeof(team_t) *
    my_len(NULL, (void **)zappy->teams_name));
    if (zappy->teams == NULL)
        return perror("load_zappy_team");
    for (int i = 0; zappy->teams_name[i] != NULL; i++)
        zappy->teams[i] = init_team(zappy->teams_name[i], zappy->team_size);
}

/// @brief Free the given team
/// @param team Team to free
static void free_team(team_t *team)
{
    if (team == NULL)
        return;
    free_players(team);
    free(team->team_name);
    free(team);
}

/// @brief Free all teams from the Zappy
/// @param zappy Structure that contains all games information
void free_teams(zappy_t *zappy)
{
    int len = 0;

    if (zappy == NULL)
        return;
    len = my_len(NULL, (void **)zappy->teams_name);
    for (int i = 0; i < len; i++)
        free_team(zappy->teams[i]);
    free(zappy->teams);
}
