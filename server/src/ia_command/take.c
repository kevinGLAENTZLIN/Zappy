/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Take
*/

#include "../../include/server.h"

static void take_object2(server_t *server, int i, char *object, tile_t *tile)
{
    bool tmp = (strcmp(object, "thystame") == 0 && tile->thystame > 0);

    if (strcmp(object, "sibur") == 0 && tile->sibur > 0) {
        PLAYER->sibur += 1;
        tile->sibur -= 1;
        return (void)dprintf(FD_CLIENT, "ok\n");
    }
    if (strcmp(object, "mendiane") == 0 && tile->mendiane > 0) {
        PLAYER->mendiane += 1;
        tile->mendiane -= 1;
        return (void)dprintf(FD_CLIENT, "ok\n");
    }
    if (strcmp(object, "phiras") == 0 && tile->phiras > 0) {
        PLAYER->phiras += 1;
        tile->phiras -= 1;
        return (void)dprintf(FD_CLIENT, "ok\n");
    }
    PLAYER->thystame += tmp ? 1 : 0;
    tile->thystame -= tmp ? 1 : 0;
    return (void)dprintf(FD_CLIENT, tmp ? "ok\n" : "ko\n");
}

static void take_object(server_t *server, int i, char *object)
{
    tile_t *tile = PLAYER_TILE;

    if (tile == NULL)
        return (void)dprintf(FD_CLIENT, "ko\n");
    if (strcmp(object, "food") == 0 && tile->food > 0) {
        PLAYER->food += 1;
        tile->food -= 1;
        return (void)dprintf(FD_CLIENT, "ok\n");
    }
    if (strcmp(object, "linemate") == 0 && tile->linemate > 0) {
        PLAYER->linemate += 1;
        tile->linemate -= 1;
        return (void)dprintf(FD_CLIENT, "ok\n");
    }
    if (strcmp(object, "deraumere") == 0 && tile->deraumere > 0) {
        PLAYER->deraumere += 1;
        tile->deraumere -= 1;
        return (void)dprintf(FD_CLIENT, "ok\n");
    }
    take_object2(server, i, object, tile);
}

void take(server_t *server, int i, char *input)
{
    char **tab = get_parameters(input);

    if (tab == NULL || tab[0] == NULL || tab[1] == NULL)
        return (void)dprintf(FD_CLIENT, "ko\n");
    take_object(server, i, tab[1]);
    free_tab(tab);
}
