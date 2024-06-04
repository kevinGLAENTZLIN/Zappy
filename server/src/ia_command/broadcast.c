/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Broadcast
*/

#include "../../include/server.h"

static int get_way_direction(double angle)
{
    if (angle <= -67.5 && angle >= -112.5)
        return 0;
    if (angle < -22.5 && angle > 67.5)
        return 1;
    if (angle <= 22.5 && angle >= -22.5)
        return 2;
    if (angle < 67.5 && angle > 22.5)
        return 3;
    if (angle <= 112.5 && angle >= 67.5)
        return 4;
    if (angle < 157.5 && angle > 112.5)
        return 5;
    if (angle <= -157.5 || angle >= 157.5)
        return 6;
    if (angle < -112.5 && angle > -157.5)
        return 7;
    return -42;
}

static int get_client_tile(int direction, player_t *player)
{
    return (2 * player->direction - direction + 4) % 8;
}

static void get_shortest_way(server_t *server, int i, player_t *player,
    char *input)
{
    player_t *player2 = PLAYER;
    client_t *tmp = get_client_by_player(server, player);
    int x = player2->x - player->x;
    int y = player2->y - player->y;
    double angle = atan2(y, x) * 180 / M_PI;
    int tile = get_client_tile(get_way_direction(angle), player);

    if (tmp == NULL)
        return;
    send_client(tmp->fd, "message %d, %s\n", tile, &input[10]);
}

static void get_shortest_way_players(server_t *server, int i, player_t *player,
    char *input)
{
    if (player == NULL)
        return;
    if (player == PLAYER)
        return get_shortest_way_players(server, i, player->next, input);
    get_shortest_way(server, i, player, input);
    get_shortest_way_players(server, i, player->next, input);
}

void broadcast(server_t *server, int i, char *input)
{
    client_t *client = CLIENT;

    if (client->player != NULL) {
        for (int j = 0; ZAPPY->teams_name[j] != NULL; j++) {
            get_shortest_way_players(server, i, ZAPPY->teams[j]->players,
            input);
        }
        send_to_all_gui(server, "pbc #%d %s\n", client->player->id,
        &input[10]);
        send_client(client->fd, "ok\n");
        client->time_to_wait = 7;
    }
}
