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
