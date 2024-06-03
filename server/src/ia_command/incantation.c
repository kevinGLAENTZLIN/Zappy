/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Incantation
*/

#include "../../include/server.h"

static void elevate_player_on_tile(server_t *server, int x, int y, int lvl)
{
    player_t *tmp = NULL;

    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        tmp = TEAM->players;
        while (tmp != NULL) {
            tmp->level += (tmp->x == x && tmp->y == y && tmp->level == lvl);
            tmp = tmp->next;
        }
    }
}

static void remove_resources(char *resrc, tile_t *tile)
{
    for (int j = 0; resrc[j] != 0; j++) {
        if (resrc[j] == 'D')
            tile->deraumere -= 1;
        if (resrc[j] == 'L')
            tile->linemate -= 1;
        if (resrc[j] == 'M')
            tile->mendiane -= 1;
        if (resrc[j] == 'P')
            tile->phiras -= 1;
        if (resrc[j] == 'S')
            tile->sibur -= 1;
        if (resrc[j] == 'T')
            tile->thystame -= 1;
    }
}

static void incantation_player_checking(server_t *server, int i,
    player_t *player)
{
    player_t *player2 = PLAYER;
    if (player == NULL)
        return;
    if (player->x == player2->x && player->y == player2->y &&
    player->level == player2->level)
        send_to_all_gui(server, " #%d", player->id);
    incantation_player_checking(server, i, player->next);
}

static void incantation_response(server_t *server, int i)
{
    client_t *client = CLIENT;
    player_t *player = client->player;
    char *gui_tmp = malloc(sizeof(char) * 48);
    char *ai_tmp = malloc(sizeof(char) * 48);

    send_to_all_gui(server, "pic %d %d %d", player->x, player->y,
    player->level + 1);
    for (int j = 0; ZAPPY->teams_name[j] != NULL; j++)
        incantation_player_checking(server, i, ZAPPY->teams[j]->players);
    send_to_all_gui(server, "\n");
    dprintf(client->fd, "Elevation underway\n");
    elevate_player_on_tile(server, player->x, player->y, player->level);
    sprintf(ai_tmp, "Current level: %d\n", player->level + 1);
    client->ai_action_message = ai_tmp;
    sprintf(gui_tmp, "pie %d %d ok\n", player->x, player->y);
    client->gui_action_message = gui_tmp;
    client->time_to_wait = 300;
}

static void check_incantation3(server_t *server, int i, int lvl)
{
    tile_t *tile = PLAYER_TILE;
    int nb_incantor = NB_INCANTOR(lvl);

    if (lvl == 5 && tile->linemate >= 1 && tile->sibur >= 3 && tile->phiras >=
        1 && tile->deraumere >= 2 && nb_incantor >= 6) {
        remove_resources("LDDSSSP", tile);
        return incantation_response(server, i);
    }
    if (lvl == 6 && tile->linemate >= 2 && tile->deraumere >= 2 && tile->sibur
        >= 2 && tile->phiras >= 2 && tile->mendiane >= 2 && tile->thystame >= 1
        && nb_incantor >= 6) {
        remove_resources("LLDDSSMMPPT", tile);
        return incantation_response(server, i);
    }
    send_to_all_gui(server, "pie %d %d ko\n", tile->x, tile->y);
    return (void)dprintf(FD_CLIENT, "ko\n");
}

static void check_incantation2(server_t *server, int i, int lvl)
{
    tile_t *tile = PLAYER_TILE;
    int nb_incantor = NB_INCANTOR(lvl);

    if (lvl == 3 && tile->linemate >= 1 && tile->deraumere >= 1 && tile->sibur
        >= 2 && tile->phiras >= 1 && nb_incantor >= 4) {
        remove_resources("LDSSP", tile);
        return incantation_response(server, i);
    }
    if (lvl == 4 && tile->linemate >= 1 && tile->deraumere >= 2 && tile->sibur
        >= 1 && tile->mendiane >= 3 && nb_incantor >= 4) {
        remove_resources("LDDSMMM", tile);
        return incantation_response(server, i);
    }
    check_incantation3(server, i, lvl);
}

static void check_incantation1(server_t *server, int i, int lvl)
{
    tile_t *tile = PLAYER_TILE;
    int nb_incantor = NB_INCANTOR(lvl);

    if (lvl == 0 && tile->linemate >= 1 && nb_incantor >= 1) {
        remove_resources("L", tile);
        return incantation_response(server, i);
    }
    if (lvl == 1 && tile->linemate >= 1 && tile->deraumere >= 1 && tile->sibur
        >= 1 && nb_incantor >= 2) {
        remove_resources("LDS", tile);
        return incantation_response(server, i);
    }
    if (lvl == 2 && tile->linemate >= 2 && tile->sibur >= 1 && tile->phiras >=
        2 && nb_incantor >= 2) {
        remove_resources("LLPPS", tile);
        return incantation_response(server, i);
    }
    check_incantation2(server, i, lvl);
}

void incantation(server_t *server, int i, char *input)
{
    player_t *player = PLAYER;
    (void) input;
    if (player != NULL) {
        check_incantation1(server, i, player->level);
    }
}
