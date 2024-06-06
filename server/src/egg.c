/*
** EPITECH PROJECT, 2024
** server
** File description:
** egg
*/

#include "../include/server.h"

/// @brief Returns the total number of egg in the Zappy structure
/// @param zappy Structure that contains al games information
/// @return Total number of eggs
static int get_nb_eggs(zappy_t *zappy)
{
    int count = 0;
    egg_t *tmp = zappy->eggs;

    while (tmp != NULL) {
        count += 1;
        tmp = tmp->next;
    }
    return count;
}

/// @brief Initialize an egg to the given coordinates
/// @param x Coordinate on X axis
/// @param y Coordinate on Y axis
/// @param team Team of the egg
/// @param id Egg ID
/// @return Egg to the given coordinates
static egg_t *init_egg(int x, int y, team_t *team, int id)
{
    egg_t *tmp = malloc(sizeof(egg_t));

    if (tmp == NULL)
        return (egg_t *)my_perror("init_egg");
    tmp->id = id;
    tmp->x = x;
    tmp->y = y;
    tmp->team_name = strdup(team->team_name);
    if (tmp->team_name == NULL)
        return (egg_t *)my_perror("init_egg");
    tmp->next = NULL;
    return tmp;
}

/// @brief Initialize and push an egg to the list of egg
/// @param zappy Structure that contains al games information
/// @param x Coordinate on X axis
/// @param y Coordinate on Y axis
/// @param team Team of the egg
/// @return Initialized egg pointer
egg_t *push_back_egg(zappy_t *zappy, int x, int y, team_t *team)
{
    egg_t *tmp = zappy->eggs;
    int id = get_nb_eggs(zappy);

    if (tmp == NULL) {
        zappy->eggs = init_egg(x, y, team, id);
        return zappy->eggs;
    } else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = init_egg(x, y, team, id);
    }
    return tmp->next;
}

/// @brief Returns the total number of egg in the given team
/// @param server Structure that contain all server data
/// @param team Team of the egg
/// @return Total number of egg in the given team
static int get_nb_team_egg(server_t *server, team_t *team)
{
    int count = 0;
    egg_t *tmp = ZAPPY->eggs;

    while (tmp != NULL) {
        count += (strcmp(tmp->team_name, team->team_name) == 0);
        tmp = tmp->next;
    }
    return count;
}

/// @brief Randomly returned one egg of the given team
/// @param server Structure that contain all server data
/// @param team Team of the egg
/// @return A random egg of the team
egg_t *get_random_egg(server_t *server, team_t *team)
{
    int n = 0;
    egg_t *tmp = ZAPPY->eggs;

    srand(time(NULL));
    n = rand() % get_nb_team_egg(server, team);
    if (get_nb_team_egg(server, team) == 0)
        return NULL;
    while (tmp != NULL) {
        if (n == 0 && strcmp(tmp->team_name, team->team_name) == 0)
            return tmp;
        if (strcmp(tmp->team_name, team->team_name) == 0)
            n -= 1;
        tmp = tmp->next;
    }
    return NULL;
}

/// @brief Initialize N random egg of the given team on the map
/// @param zappy Structure that contains al games information
/// @param team Team of the egg
/// @param n Number of eggs wanted
void set_n_random_egg(zappy_t *zappy, team_t *team, int n)
{
    int x = 0;
    int y = 0;

    for (int j = 0; j < n; j++) {
        x = rand() % zappy->x;
        y = rand() % zappy->y;
        push_back_egg(zappy, x, y, team);
    }
}

/// @brief Free the given egg
/// @param egg Egg you want to free
static void free_egg(egg_t *egg)
{
    if (egg == NULL)
        return;
    if (egg->team_name != NULL)
        free(egg->team_name);
    free(egg);
}

/// @brief Free and remove the given egg from the egg list
/// @param server Structure that contain all server data
/// @param egg Egg you want to remove
void hatch_egg(server_t *server, egg_t *egg)
{
    egg_t *tmp = ZAPPY->eggs;

    if (tmp == NULL)
        return;
    if (tmp == egg) {
        ZAPPY->eggs = egg->next;
        free_egg(egg);
        return;
    }
    while (tmp->next != NULL) {
        if (tmp->next == egg) {
            tmp->next = egg->next;
            free_egg(egg);
            return;
        }
        tmp = tmp->next;
    }
}

/// @brief Free all eggs
/// @param egg Starting egg of the linked list
void free_eggs(egg_t *egg)
{
    egg_t *tmp = NULL;

    if (egg == NULL)
        return;
    tmp = egg->next;
    free_egg(egg);
    return free_eggs(tmp);
}
