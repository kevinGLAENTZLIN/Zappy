/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Broadcast
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

static int get_shortest_difference(int a1, int a2, int a_max)
{
    int r1 = ((a_max - a1 + a2) + a_max * 2) % a_max;
    int r2 = ((a_max - a2 + a1) + a_max * 2) % a_max;

    return MIN(r1, r2);
}

static void get_shortest_way(server_t *server, int i, player_t *player)
{
    int x = get_shortest_difference(player->x, PLAYER->x, ZAPPY->x);
    int y = get_shortest_difference(player->y, PLAYER->y, ZAPPY->y);
    client_t *tmp = get_client_by_player(server, player);

    send_to_all_gui(server, "pbc #%d\n", tmp->player->id);
    dprintf(tmp->fd, "Broadcast: %d %d\n", x, y);
}

static void get_shortest_way_players(server_t *server, int i, player_t *player)
{
    if (player == NULL)
        return;
    if (player == PLAYER)
        return get_shortest_way_players(server, i, player->next);
    get_shortest_way(server, i, player);
    get_shortest_way_players(server, i, player->next);
}

void broadcast(server_t *server, int i, char *input)
{
    (void) input;
    if (PLAYER != NULL) {
        for (int i = 0; ZAPPY->teams_name[i] != NULL; i++)
            get_shortest_way_players(server, i, TEAM->players);
        dprintf(FD_CLIENT, "ok\n");
        CLIENT->time_to_wait = 7;
    }
}
