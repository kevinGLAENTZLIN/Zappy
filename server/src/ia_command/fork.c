/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Fork
*/

#include "../../include/server.h"

void my_fork(server_t *server, int i, char *input)
{
    client_t *client = CLIENT;
    team_t *team = NULL;
    egg_t *egg = NULL;
    char *tmp = NULL;

    (void) input;
    if (client->player != NULL) {
        team = get_team_by_name(server, client->player->team_name);
        egg = push_back_egg(ZAPPY, client->player->x, client->player->y, team);
        team->nb_max_player += 1;
        send_to_all_gui(server, "pfk #%d\n", client->player->id);
        tmp = malloc(sizeof(char) * 64);
        if (tmp == NULL)
            return perror("my_fork");
        sprintf(tmp, "enw #%d #%d %d %d\n", egg->id, client->player->id,
        egg->x, egg->y);
        client->gui_action_message = tmp;
        send_client(client->fd, "ok\n");
        client->time_to_wait = 42;
    }
}
