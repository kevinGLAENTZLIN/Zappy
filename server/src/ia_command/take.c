/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Take
*/

#include "../../include/server.h"

/// @brief Send to all the GUI client the take command answer
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param object Type of the object take
static void handle_take_response(server_t *server, int i, char *object)
{
    player_t *player = PLAYER;

    if (strcmp(object, "food") == 0)
        send_to_all_gui(server, "pgt #%d %d\n", player->id, 0);
    if (strcmp(object, "linemate") == 0)
        send_to_all_gui(server, "pgt #%d %d\n", player->id, 1);
    if (strcmp(object, "deraumere") == 0)
        send_to_all_gui(server, "pgt #%d %d\n", player->id, 2);
    if (strcmp(object, "sibur") == 0)
        send_to_all_gui(server, "pgt #%d %d\n", player->id, 3);
    if (strcmp(object, "mendiane") == 0)
        send_to_all_gui(server, "pgt #%d %d\n", player->id, 4);
    if (strcmp(object, "phiras") == 0)
        send_to_all_gui(server, "pgt #%d %d\n", player->id, 5);
    if (strcmp(object, "thystame") == 0)
        send_to_all_gui(server, "pgt #%d %d\n", player->id, 6);
    send_client(FD_CLIENT, "ok\n");
}

/// @brief Take the given object on the Player tile
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param object Type of the object take
static void take_object3(server_t *server, int i, char *object, tile_t *tile)
{
    if (strcmp(object, "thystame") == 0 && tile->thystame > 0) {
        PLAYER->thystame += 1;
        tile->thystame -= 1;
        return handle_take_response(server, i, object);
    }
    return (void)send_client(FD_CLIENT, "ko\n");
}

/// @brief Take the given object on the Player tile
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param object Type of the object take
static void take_object2(server_t *server, int i, char *object, tile_t *tile)
{
    if (strcmp(object, "sibur") == 0 && tile->sibur > 0) {
        PLAYER->sibur += 1;
        tile->sibur -= 1;
        return handle_take_response(server, i, object);
    }
    if (strcmp(object, "mendiane") == 0 && tile->mendiane > 0) {
        PLAYER->mendiane += 1;
        tile->mendiane -= 1;
        return handle_take_response(server, i, object);
    }
    if (strcmp(object, "phiras") == 0 && tile->phiras > 0) {
        PLAYER->phiras += 1;
        tile->phiras -= 1;
        return handle_take_response(server, i, object);
    }
    take_object3(server, i, object, tile);
}

/// @brief Take the given object on the Player tile
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param object Type of the object take
static void take_object(server_t *server, int i, char *object)
{
    tile_t *tile = PLAYER_TILE;

    if (tile == NULL)
        return (void)send_client(FD_CLIENT, "ko\n");
    if (strcmp(object, "food") == 0 && tile->food > 0) {
        PLAYER->food += 1;
        tile->food -= 1;
        return handle_take_response(server, i, object);
    }
    if (strcmp(object, "linemate") == 0 && tile->linemate > 0) {
        PLAYER->linemate += 1;
        tile->linemate -= 1;
        return handle_take_response(server, i, object);
    }
    if (strcmp(object, "deraumere") == 0 && tile->deraumere > 0) {
        PLAYER->deraumere += 1;
        tile->deraumere -= 1;
        return handle_take_response(server, i, object);
    }
    take_object2(server, i, object, tile);
}

/// @brief Take command of the Client protocol
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
void take(server_t *server, int i, char *input)
{
    client_t *client = CLIENT;
    char **tab = get_parameters(input);

    if (tab == NULL || tab[0] == NULL || tab[1] == NULL)
        return (void)send_client(client->fd, "ko\n");
    take_object(server, i, tab[1]);
    client->time_to_wait = 7;
    free_tab(tab);
}
