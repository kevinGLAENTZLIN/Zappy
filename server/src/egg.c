/*
** EPITECH PROJECT, 2024
** server
** File description:
** egg
*/

#include "../include/server.h"

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

static egg_t *init_egg(int x, int y, team_t *team, int id)
{
    egg_t *tmp = malloc(sizeof(egg_t));

    if (tmp == NULL)
        return NULL;
    tmp->id = id;
    tmp->x = x;
    tmp->y = y;
    tmp->team_name = strdup(team->team_name);
    tmp->next = NULL;
    return tmp;
}

void push_back_egg(zappy_t *zappy, int x, int y, team_t *team)
{
    egg_t *tmp = zappy->eggs;
    int id = get_nb_eggs(zappy);

    if (tmp == NULL)
        zappy->eggs = init_egg(x, y, team, id);
    else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = init_egg(x, y, team, id);
    }
}

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

static void free_egg(egg_t *egg)
{
    if (egg == NULL)
        return;
    if (egg->team_name != NULL)
        free(egg->team_name);
    free(egg);
}

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

void free_eggs(egg_t *egg)
{
    egg_t *tmp = NULL;

    if (egg == NULL)
        return;
    tmp = egg->next;
    free_egg(egg);
    return free_eggs(tmp);
}
