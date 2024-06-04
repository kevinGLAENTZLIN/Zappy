/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Eject
*/

#include "../../include/server.h"

static void send_eject(server_t *server, int i, player_t *player)
{
    client_t *client = CLIENT;
    client_t *tmp = get_client_by_player(server, player);
    int a = player->direction;
    int b = client->player->direction;

    if (tmp == NULL)
        return (void)send_client(client->fd, "ko\n");
    send_client(client->fd, "ok\n");
    send_to_all_gui(server, "pex #%d\n", tmp->player->id);
    send_client(tmp->fd, "eject: %d\n", (((2 * (a - b) + 4) + 16) % 8) + 1);
}

static void destroy_egg(server_t *server, egg_t *egg)
{
    team_t *tmp = get_team_by_name(server, egg->team_name);

    if (tmp != NULL)
        tmp->nb_max_player -= 1;
    send_to_all_gui(server, "edi #%d\n", egg->id);
    hatch_egg(server, egg);
}

static void egg_destruction(server_t *server, player_t *player)
{
    egg_t *tmp = ZAPPY->eggs;
    egg_t *tmp2 = NULL;

    if (tmp == NULL)
        return;
    while (tmp != NULL) {
        if (tmp->x == player->x && tmp->y == player->y) {
            tmp2 = tmp->next;
            destroy_egg(server, tmp);
            tmp = tmp2;
        } else
            tmp = tmp->next;
    }
}

static void eject_players(server_t *server, int i, player_t *tmp)
{
    player_t *player = PLAYER;

    if (tmp == NULL)
        return;
    if (tmp == player || tmp->x != player->x || tmp->y != player->y)
        return eject_players(server, i, tmp->next);
    if (player->direction == up)
        tmp->y = ((player->y - 1) + ZAPPY->y) % ZAPPY->y;
    if (player->direction == right)
        tmp->x = ((player->x + 1) + ZAPPY->x) % ZAPPY->x;
    if (player->direction == down)
        tmp->y = ((player->y + 1) + ZAPPY->y) % ZAPPY->y;
    if (player->direction == left)
        tmp->x = ((player->x - 1) + ZAPPY->x) % ZAPPY->x;
    egg_destruction(server, tmp);
    send_eject(server, i, tmp);
    eject_players(server, i, tmp->next);
}

void eject(server_t *server, int i, char *input)
{
    client_t *client = CLIENT;

    (void) input;
    if (client->player != NULL) {
        for (int j = 0; ZAPPY->teams_name[j] != NULL; j++)
            eject_players(server, j, ZAPPY->teams[j]->players);
        client->time_to_wait = 7;
    }
}
