/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Broadcast
*/

#include "../../include/server.h"

static int get_shortest_difference(int a1, int a2, int a_max)
{
    int r1 = ((a_max - a1 + a2) + a_max * 2) % a_max;
    int r2 = ((a_max - a2 + a1) + a_max * 2) % a_max;

    return MIN(r1, r2);
}

static void get_shortest_way(server_t *server, int i, player_t *player)
{
    player_t *player2 = PLAYER;
    int x = get_shortest_difference(player->x, player2->x, ZAPPY->x);
    int y = get_shortest_difference(player->y, player2->y, ZAPPY->y);
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
    client_t *client = CLIENT;

    (void) input;
    if (client->player != NULL) {
        for (int j = 0; ZAPPY->teams_name[j] != NULL; j++)
            get_shortest_way_players(server, j, ZAPPY->teams[j]->players);
        dprintf(client->fd, "ok\n");
        client->time_to_wait = 7;
    }
}
