/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Look
*/

#include "../../include/server.h"

static bool send_tile_info(server_t *server, int i, bool opt, char *txt)
{
    if (opt)
        dprintf(FD_CLIENT, " %s", txt);
    else
        dprintf(FD_CLIENT, "%s", txt);
    return true;
}

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
        dprintf(FD_CLIENT, ", ");
}

static int n_square(int n)
{
    int ret = pow(n, 2);

    if (n == 0)
        ret = 0;
    return ret;
}

static void display_look_level(server_t *server, int i, int x, int y)
{
    bool o = true;
    int tmp = (n_square(PLAYER->level + 1) - n_square(PLAYER->level));

    for (int j = 0; j < tmp; j++) {
        if (j + 1 == tmp)
            o = false;
        if (PLAYER->direction == up)
            get_tile_info(server, i, MAP[y][(x + j + (ZAPPY->x * 8)) %
            ZAPPY->x], o);
        if (PLAYER->direction == right)
            get_tile_info(server, i, MAP[(y + j + (ZAPPY->y * 8)) %
            ZAPPY->y][x], o);
        if (PLAYER->direction == down)
            get_tile_info(server, i, MAP[y][(x - j + (ZAPPY->x * 8)) %
            ZAPPY->x], o);
        if (PLAYER->direction == left)
            get_tile_info(server, i, MAP[(y - j + (ZAPPY->y * 8)) %
            ZAPPY->y][x], o);
    }
}

static void get_look_origin_level(server_t *server, int i, int x, int y)
{
    if (PLAYER->direction == up) {
        y = ((PLAYER->y - PLAYER->level) + (ZAPPY->y * 8)) % ZAPPY->y;
        x = ((PLAYER->x - PLAYER->level) + (ZAPPY->x * 8)) % ZAPPY->x;
    }
    if (PLAYER->direction == right) {
        x = ((PLAYER->x + PLAYER->level) + (ZAPPY->x * 8)) % ZAPPY->x;
        y = ((PLAYER->y - PLAYER->level) + (ZAPPY->y * 8)) % ZAPPY->y;
    }
    if (PLAYER->direction == down) {
        y = ((PLAYER->y + PLAYER->level) + (ZAPPY->y * 8)) % ZAPPY->y;
        x = ((PLAYER->x + PLAYER->level) + (ZAPPY->x * 8)) % ZAPPY->x;
    }
    if (PLAYER->direction == left) {
        x = ((PLAYER->x - PLAYER->level) + (ZAPPY->x * 8)) % ZAPPY->x;
        y = ((PLAYER->y + PLAYER->level) + (ZAPPY->y * 8)) % ZAPPY->y;
    }
    display_look_level(server, i, x, y);
}

static void display_look(server_t *server, int i)
{
    int tmp = PLAYER->level + 2;

    dprintf(FD_CLIENT, "[");
    for (int j = 0; j < tmp; j++) {
        PLAYER->level = j;
        get_look_origin_level(server, i, PLAYER->x, PLAYER->y);
        if (j + 1 != tmp)
            dprintf(FD_CLIENT, ", ");
    }
    dprintf(FD_CLIENT, "]\n");
    PLAYER->level = tmp - 2;
    CLIENT->time_to_wait = 7;
}

void look(server_t *server, int i, char *input)
{
    (void) input;
    if (PLAYER != NULL)
        display_look(server, i);
}
