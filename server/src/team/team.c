/*
** EPITECH PROJECT, 2024
** server
** File description:
** team
*/

#include "../../include/server.h"

/// @brief Returns if the given name is a string name
/// @param server Structure that contain all server data
/// @return True if it's a team name, else False
bool is_team_name(server_t *server, const char *name)
{
    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        if (strncmp(ZAPPY->teams_name[i], name,
        strlen(ZAPPY->teams_name[i])) == 0)
            return true;
    }
    return false;
}

/// @brief Returns the team relative to the given name
/// @param server Structure that contain all server data
/// @param name Name of the team
/// @return NULL if no team found, else the relative team
team_t *get_team_by_name(server_t *server, const char *name)
{
    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        if (name != NULL && strncmp(TEAM_NAME, name, strlen(TEAM_NAME)) == 0)
            return TEAM;
    }
    return NULL;
}
