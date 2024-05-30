/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Fork
*/

#include "../../include/server.h"

void my_fork(server_t *server, int i, char *input)
{
    team_t *team = NULL;

    (void) input;
    if (PLAYER != NULL) {
        team = get_team_by_name(server, PLAYER->team_name);
        push_back_egg(server, PLAYER->x, PLAYER->y, team);
        team->nb_max_player += 1;
        dprintf(FD_CLIENT, "ok\n");
    }
}
