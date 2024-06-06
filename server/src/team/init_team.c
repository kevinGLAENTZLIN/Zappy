/*
** EPITECH PROJECT, 2024
** server
** File description:
** team
*/

#include "../../include/server.h"

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

static void free_team(team_t *team)
{
    if (team == NULL)
        return;
    free_players(team);
    free(team->team_name);
    free(team);
}

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
