/*
** EPITECH PROJECT, 2024
** server
** File description:
** team
*/

#include "../../include/server.h"

bool is_team_name(server_t *server, const char *name)
{
    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        if (strncmp(ZAPPY->teams_name[i], name,
        strlen(ZAPPY->teams_name[i])) == 0)
            return true;
    }
    return false;
}

team_t *get_team_by_name(server_t *server, const char *name)
{
    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        if (name != NULL && strncmp(TEAM_NAME, name, strlen(TEAM_NAME)) == 0)
            return TEAM;
    }
    return NULL;
}
