/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Eject
*/

#include "../../include/server.h"

static client_t *get_client_by_player(server_t *server, player_t *player)
{
    for (int i = 0; i < server->nb_client; i++) {
        if (strcmp(CLIENT_TYPE, IA) == 0 && PLAYER == player)
            return CLIENT;
    }
    return NULL;
}

static void send_eject(server_t *server, int i, player_t *player)
{
    client_t *tmp = get_client_by_player(server, player);
    int a = player->direction;
    int b = PLAYER->direction;

    if (tmp == NULL)
        return (void)dprintf(FD_CLIENT, "ko\n");
    dprintf(FD_CLIENT, "ok\n");
    send_to_all_gui(server, "pex #%d\n", tmp->player->id);
    dprintf(tmp->fd, "eject: %d\n", (((2 * (a - b) + 4) + 16) % 8) + 1);
}

static void destroy_egg(server_t *server, egg_t *egg)
{
    team_t *tmp = get_team_by_name(server, egg->team_name);

    if (tmp != NULL)
        tmp->nb_max_player -= 1;
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

static void eject_players(server_t *server, int i, player_t *player)
{
    if (player == NULL)
        return;
    if (player == PLAYER || player->x != PLAYER->x || player->y != PLAYER->y)
        return eject_players(server, i, player->next);
    if (PLAYER->direction == up)
        player->y = ((PLAYER->y - 1) + ZAPPY->y) % ZAPPY->y;
    if (PLAYER->direction == right)
        player->x = ((PLAYER->x + 1) + ZAPPY->x) % ZAPPY->x;
    if (PLAYER->direction == down)
        player->y = ((PLAYER->y + 1) + ZAPPY->y) % ZAPPY->y;
    if (PLAYER->direction == left)
        player->x = ((PLAYER->x - 1) + ZAPPY->x) % ZAPPY->x;
    egg_destruction(server, player);
    send_eject(server, i, player);
    eject_players(server, i, player->next);
}

void eject(server_t *server, int i, char *input)
{
    (void) input;
    if (PLAYER != NULL) {
        for (int i = 0; ZAPPY->teams_name[i] != NULL; i++)
            eject_players(server, i, TEAM->players);
    }
}
