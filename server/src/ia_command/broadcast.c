/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Broadcast
*/

#include "../../include/server.h"

/// @brief Return the direction to go on the X axis and the distance between
/// bx and rx
/// @param bx Coordinates on the X axis of the Broadcaster
/// @param rx Coordinates on the X axis of the Receiver
/// @param max_x Size of the map on the X axis
/// @return Smallest distance between the Broadcaster and Receiver on X axis
static int get_x_direction(int bx, int rx, int max_x)
{
    if (MAX(bx, rx) - MIN(bx, rx) > max_x / 2) {
        if (bx < max_x / 2)
            return -(max_x - rx + bx);
        else
            return (max_x - bx + rx);
    } else
        if (bx < max_x / 2)
            return (rx - bx);
        else
            return -(bx - rx);
}

/// @brief Return the direction to go on the Y axis and the distance between
/// by and ry
/// @param by Coordinates on the Y axis of the Broadcaster
/// @param ry Coordinates on the Y axis of the Receiver
/// @param max_x Size of the map on the Y axis
/// @return Smallest distance between the Broadcaster and Receiver on Y axis
static int get_y_direction(int by, int ry, int max_y)
{
    if (MAX(by, ry) - MIN(by, ry) > max_y / 2) {
        if (by < max_y / 2)
            return -(max_y - ry + by);
        else
            return (max_y - by + ry);
    } else
        if (by < max_y / 2)
            return (ry - by);
        else
            return -(by - ry);
}

/// @brief Get the direction of the path
/// @param angle Angle of the path
/// @return Tile position of the path
static int get_way_direction(double angle)
{
    if (angle < -45. && angle > -135.)
        return 0;
    if (angle == -45.)
        return 1;
    if (angle < 45. && angle > -45.)
        return 2;
    if (angle == 45.)
        return 3;
    if (angle < 135 && angle > 45)
        return 4;
    if (angle == 135.)
        return 5;
    if (angle < -135 || angle > 135)
        return 6;
    if (angle == -135.)
        return 7;
    return -42;
}

/// @brief Get the relative position of the direction of the broadcast based on
/// the given player
/// @param direction Direction of the broadcast
static int get_client_tile(int direction, player_t *player)
{
    return ((2 * player->direction - direction + 4) % 8) + 1;
}

/// @brief Broadcast to the given player
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
static void get_shortest_way(server_t *server, int i, player_t *player,
    char *input)
{
    player_t *player2 = PLAYER;
    client_t *tmp = get_client_by_player(server, player);
    int x = get_x_direction(player2->x, player->x, ZAPPY->x);
    int y = get_y_direction(player2->y, player->y, ZAPPY->y);
    double angle = atan2(y, x) * 180 / M_PI;
    int tile = get_client_tile(get_way_direction(angle), player);

    if (tmp == NULL)
        return;
    send_client(tmp->fd, "message %d, %s\n", tile, &input[10]);
}

/// @brief Broadcast to the list of player
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param player Players list of a team
/// @param input Command input from the Client
static void get_shortest_way_players(server_t *server, int i, player_t *player,
    char *input)
{
    player_t *player2 = PLAYER;

    if (player == NULL)
        return;
    if (player == player2)
        return get_shortest_way_players(server, i, player->next, input);
    if (player->x == player2->x && player->y == player2->y) {
        send_client(get_client_by_player(server, player)->fd,
        "message %d, %s\n", 0, &input[10]);
        return get_shortest_way_players(server, i, player->next, input);
    }
    get_shortest_way(server, i, player, input);
    get_shortest_way_players(server, i, player->next, input);
}

/// @brief Broadcast command of the Client protocol
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
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
