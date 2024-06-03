/*
** EPITECH PROJECT, 2024
** server
** File description:
** map
*/

#include "../include/server.h"

/// @brief Initialize a default tile to the given coordinate
/// @param x Coordinate on X axis
/// @param y Coordinate on Y axis
/// @return A default tile  to the given coordinate
static tile_t *init_tile(int x, int y)
{
    tile_t *tmp = malloc(sizeof(tile_t));

    if (tmp == NULL)
        return NULL;
    tmp->x = x;
    tmp->y = y;
    tmp->deraumere = 0;
    tmp->food = 0;
    tmp->linemate = 0;
    tmp->mendiane = 0;
    tmp->phiras = 0;
    tmp->sibur = 0;
    tmp->thystame = 0;
    return tmp;
}

/// @brief Initialize a default game map
/// @param zappy Structure that contains the map size
void init_map(zappy_t *zappy)
{
    tile_t ***map = malloc(sizeof(tile_t **) * (zappy->y * zappy->x));

    if (map == NULL) {
        zappy->map = NULL;
        return;
    }
    for (int y = 0; y < zappy->y; y++) {
        map[y] = malloc(sizeof(tile_t *) * zappy->x);
        for (int x = 0; x < zappy->x; x++) {
            map[y][x] = init_tile(x, y);
        }
    }
    zappy->map = map;
}

/// @brief Randomly spread out resource on the whole map
/// @param zappy Structure that contains all games information
/// @param f Number of resources that have to be spawned
/// @param type Resource type
static void set_resource(zappy_t *zappy, float f, char *type)
{
    int n = (int)f;

    for (int j = 0; j < n; j++) {
        if (strcmp(type, "food") == 0)
            zappy->map[rand() % zappy->y][rand() % zappy->x]->food += 1;
        if (strcmp(type, "linemate") == 0)
            zappy->map[rand() % zappy->y][rand() % zappy->x]->linemate += 1;
        if (strcmp(type, "deraumere") == 0)
            zappy->map[rand() % zappy->y][rand() % zappy->x]->deraumere += 1;
        if (strcmp(type, "sibur") == 0)
            zappy->map[rand() % zappy->y][rand() % zappy->x]->sibur += 1;
        if (strcmp(type, "mendiane") == 0)
            zappy->map[rand() % zappy->y][rand() % zappy->x]->mendiane += 1;
        if (strcmp(type, "phiras") == 0)
            zappy->map[rand() % zappy->y][rand() % zappy->x]->phiras += 1;
        if (strcmp(type, "thystame") == 0)
            zappy->map[rand() % zappy->y][rand() % zappy->x]->thystame += 1;
    }
}

/// @brief Randomly generate all resources on the map
/// @param zappy Structure that contains all games information
void set_map_resources(zappy_t *zappy)
{
    if (zappy->map == NULL)
        return;
    set_resource(zappy, zappy->x * zappy->y * 0.5, "food");
    set_resource(zappy, zappy->x * zappy->y * 0.3, "linemate");
    set_resource(zappy, zappy->x * zappy->y * 0.15, "deraumere");
    set_resource(zappy, zappy->x * zappy->y * 0.1, "sibur");
    set_resource(zappy, zappy->x * zappy->y * 0.1, "mendiane");
    set_resource(zappy, zappy->x * zappy->y * 0.08, "phiras");
    set_resource(zappy, zappy->x * zappy->y * 0.05, "thystame");
}

/// @brief Free the game map
/// @param zappy Structure that contains all games information
void free_map(zappy_t *zappy)
{
    if (zappy == NULL || zappy->map == NULL)
        return;
    for (int y = 0; y < zappy->y; y++) {
        for (int x = 0; x < zappy->x; x++) {
            free(zappy->map[y][x]);
        }
        free(zappy->map[y]);
    }
    free(zappy->map);
    zappy->map = NULL;
}

/// @brief Return the number of player on the tile at this coordinate
/// @param server Structure that contain all server data
/// @param x Coordinate on X axis
/// @param y Coordinate on Y axis
/// @return Number of player on the tile
int get_nb_player_on_tile(server_t *server, int x, int y)
{
    int count = 0;
    player_t *tmp = NULL;

    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        tmp = TEAM->players;
        while (tmp != NULL) {
            count += (tmp->x == x && tmp->y == y);
            tmp = tmp->next;
        }
    }
    return count;
}

/// @brief Return the number of player incanting on the tile at this level
/// @param server Structure that contain all server data
/// @param x Coordinate on X axis
/// @param y Coordinate on Y axis
/// @param lvl Current level of Incantor
/// @return Number of incantor on the tile
int get_nb_incantor(server_t *server, int x, int y, int lvl)
{
    int count = 0;
    player_t *tmp = NULL;

    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        tmp = TEAM->players;
        while (tmp != NULL) {
            count += (tmp->x == x && tmp->y == y && tmp->level == lvl);
            tmp = tmp->next;
        }
    }
    return count;
}
