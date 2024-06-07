/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Look
*/

#include "../../include/server.h"

/// @brief Send the info to Client
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param opt If display a space or not
/// @param txt Type of object
/// @return 
static bool send_tile_info(server_t *server, int i, bool opt, char *txt)
{
    if (opt)
        send_client(FD_CLIENT, " %s", txt);
    else
        send_client(FD_CLIENT, "%s", txt);
    return true;
}

/// @brief Get and send tile info of the client
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param tile Tile to check
/// @param opt If display a comma or not
static void get_tile_info(server_t *server, int i, tile_t *tile, bool opt)
{
    bool tmp = false;

    for (int j = 0; j < get_nb_player_on_tile(server, tile->x, tile->y); j++)
        tmp = send_tile_info(server, i, tmp, "player");
    for (int j = 0; j < tile->food; j++)
        tmp = send_tile_info(server, i, tmp, "food");
    for (int j = 0; j < tile->linemate; j++)
        tmp = send_tile_info(server, i, tmp, "linemate");
    for (int j = 0; j < tile->deraumere; j++)
        tmp = send_tile_info(server, i, tmp, "deraumere");
    for (int j = 0; j < tile->mendiane; j++)
        tmp = send_tile_info(server, i, tmp, "mendiane");
    for (int j = 0; j < tile->sibur; j++)
        tmp = send_tile_info(server, i, tmp, "sibur");
    for (int j = 0; j < tile->phiras; j++)
        tmp = send_tile_info(server, i, tmp, "phiras");
    for (int j = 0; j < tile->thystame; j++)
        tmp = send_tile_info(server, i, tmp, "thystame");
    if (opt)
        send_client(FD_CLIENT, ", ");
}

/// @brief Return n power 2
/// @return if n equal 0 then returns 0, else n^2
static int n_square(int n)
{
    int ret = pow(n, 2);

    if (n == 0)
        ret = 0;
    return ret;
}

/// @brief Send the tile info to each Client
/// @param server Structure that contains all games information
/// @param i Index of the Client
static void display_look_level(server_t *server, int i, int x, int y)
{
    player_t *player = PLAYER;
    bool o = true;
    int tmp = (n_square(player->level + 1) - n_square(player->level));

    for (int j = 0; j < tmp; j++) {
        if (j + 1 == tmp)
            o = false;
        if (player->direction == up)
            get_tile_info(server, i, MAP[y][(x + j + (ZAPPY->x * 8)) %
            ZAPPY->x], o);
        if (player->direction == right)
            get_tile_info(server, i, MAP[(y + j + (ZAPPY->y * 8)) %
            ZAPPY->y][x], o);
        if (player->direction == down)
            get_tile_info(server, i, MAP[y][(x - j + (ZAPPY->x * 8)) %
            ZAPPY->x], o);
        if (player->direction == left)
            get_tile_info(server, i, MAP[(y - j + (ZAPPY->y * 8)) %
            ZAPPY->y][x], o);
    }
}

/// @brief Get the tile origin at the player level
/// @param server Structure that contains all games information
/// @param i Index of the Client
static void get_look_origin_level(server_t *server, int i, int x, int y)
{
    player_t *player = PLAYER;

    if (player->direction == up) {
        y = ((player->y - player->level) + (ZAPPY->y * 8)) % ZAPPY->y;
        x = ((player->x - player->level) + (ZAPPY->x * 8)) % ZAPPY->x;
    }
    if (player->direction == right) {
        x = ((player->x + player->level) + (ZAPPY->x * 8)) % ZAPPY->x;
        y = ((player->y - player->level) + (ZAPPY->y * 8)) % ZAPPY->y;
    }
    if (player->direction == down) {
        y = ((player->y + player->level) + (ZAPPY->y * 8)) % ZAPPY->y;
        x = ((player->x + player->level) + (ZAPPY->x * 8)) % ZAPPY->x;
    }
    if (player->direction == left) {
        x = ((player->x - player->level) + (ZAPPY->x * 8)) % ZAPPY->x;
        y = ((player->y + player->level) + (ZAPPY->y * 8)) % ZAPPY->y;
    }
    display_look_level(server, i, x, y);
}

/// @brief Send the look information to the Client 
/// @param server Structure that contains all games information
/// @param i Index of the Client
static void display_look(server_t *server, int i)
{
    client_t *client = CLIENT;
    int tmp = client->player->level + 2;

    send_client(client->fd, "[");
    for (int j = 0; j < tmp; j++) {
        client->player->level = j;
        get_look_origin_level(server, i, client->player->x, client->player->y);
        if (j + 1 != tmp)
            send_client(client->fd, ", ");
    }
    send_client(client->fd, "]\n");
    client->player->level = tmp - 2;
    client->time_to_wait = 7;
}

/// @brief Look command of the Client protocol
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
void look(server_t *server, int i, char *input)
{
    (void) input;
    if (PLAYER != NULL)
        display_look(server, i);
}
