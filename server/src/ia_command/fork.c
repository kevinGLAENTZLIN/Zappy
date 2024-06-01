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
    egg_t *egg = NULL;

    (void) input;
    if (PLAYER != NULL) {
        team = get_team_by_name(server, PLAYER->team_name);
        egg = push_back_egg(ZAPPY, PLAYER->x, PLAYER->y, team);
        team->nb_max_player += 1;
        send_to_all_gui(server, "pfk #%d\n", PLAYER->id);
        send_to_all_gui(server, "enw #%d #%d %d %d\n", egg->id, PLAYER->id,
        egg->x, egg->y);
        dprintf(FD_CLIENT, "ok\n");
        CLIENT->time_to_wait = 42;
    }
}
