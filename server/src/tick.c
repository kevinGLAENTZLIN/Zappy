/*
** EPITECH PROJECT, 2024
** server
** File description:
** tick
*/

#include "../include/server.h"

/// @brief Initialize all tick information based on the given frequence
/// @param frequence frequence of tick per seconds
/// @return The initalized tick structure
tick_t *init_tick(int frequence)
{
    tick_t *tmp = malloc(sizeof(tick_t));
    int ret = 0;

    if (tmp == NULL)
        return my_perror("init_tick");
    ret = pthread_mutex_init(&tmp->mutex_tick, NULL);
    if (ret != 0)
        return my_perror("init_tick");
    tmp->nb_ticks = 0;
    tmp->tick = 1000000 / frequence;
    tmp->last_time = (struct timeval){0, 0};
    tmp->is_threading = true;
    return tmp;
}

/// @brief Free the given tick structure
void free_tick(tick_t *tick)
{
    int ret = 0;

    if (tick == NULL)
        return;
    ret = pthread_mutex_destroy(&tick->mutex_tick);
    if (ret != 0)
        return perror("free_tick");
    free(tick);
}

/// @brief Display on a line the food number of each player at given level
/// @param server Structure that contain all server data
/// @param level Level of the players to display
void display_food_level(server_t *server, int level)
{
    client_t *client = NULL;

    for (int i = 0; i < server->nb_client; i++) {
        client = CLIENT;
        if (client != NULL && client->player != NULL &&
            client->player->level == level)
            printf(" %d", client->player->food);
    }
}

/// @brief Display the number of Player for each levels
/// @param server Structure that contain all server data
/// @param kill If true send dead to all players
void display_levels(server_t *server, bool kill)
{
    client_t *client = NULL;
    int level[8];

    for (int i = 0; i < 8; i++)
        level[i] = 0;
    for (int i = 0; i < server->nb_client; i++) {
        client = CLIENT;
        if (client == NULL || client->player == NULL)
            continue;
        level[client->player->level] += 1;
        if (kill)
            send_client(client->fd, "dead\n");
    }
    for (int j = 0; j < 8; j++) {
        printf("%s: Level %d: %d%s", INFO, j + 1, level[j],
        ((level[j] == 0 || kill) ? "" : " |"));
        if (!kill)
            display_food_level(server, j);
        printf("\n");
    }
}

/// @brief Display as the title of the Terminal Window the timer in seconds
/// @param zappy Structure that contain all game data
static void display_clock(zappy_t *zappy)
{
    int time[4];

    if (zappy == NULL || zappy->tick == NULL ||
        zappy->tick->nb_ticks <= 0 || zappy->frequence == 0)
        return;
    time[0] = zappy->tick->nb_ticks / zappy->frequence;
    time[1] = time[0] / 60;
    time[0] %= 60;
    time[2] = time[1] / 60;
    time[1] %= 60;
    time[3] = time[2] / 24;
    time[2] %= 24;
    if (time[3] > 0)
        printf("\e]2;Server time [%02d:%02d:%02d:%02d]\n\007",
        time[3], time[2], time[1], time[0]);
    else if (time[2] > 0)
        printf("\e]2;Server time [%02d:%02d:%02d]\n\007",
        time[2], time[1], time[0]);
    else
        printf("\e]2;Server time [%02d:%02d]\n\007", time[1], time[0]);
}

/// @brief Display timer in the terminal
/// @param zappy Structure that contain all game data
static void display_clock_terminal(zappy_t *zappy)
{
    int time[4];

    if (zappy == NULL || zappy->tick == NULL ||
        zappy->tick->nb_ticks <= 0 || zappy->frequence == 0)
        return;
    time[0] = zappy->tick->nb_ticks / zappy->frequence;
    time[1] = time[0] / 60;
    time[0] %= 60;
    time[2] = time[1] / 60;
    time[1] %= 60;
    time[3] = time[2] / 24;
    time[2] %= 24;
    if (time[3] > 0)
        printf("%s: Server time [%02d:%02d:%02d:%02d]\n", INFO,
        time[3], time[2], time[1], time[0]);
    else if (time[2] > 0)
        printf("%s: Server time [%02d:%02d:%02d]\n", INFO,
        time[2], time[1], time[0]);
    else
        printf("%s: Server time [%02d:%02d]\n", INFO, time[1], time[0]);
}

/// @brief Display informations concerning player every 30 seconds
/// @param server Structure that contain all server data
static void display_tick_info(server_t *server)
{
    int i = 0;

    display_clock(ZAPPY);
    if (ZAPPY->clear_line)
        printf("\033[A\r");
    ZAPPY->clear_line = true;
    if (ZAPPY->tick->nb_ticks % (30 * ZAPPY->frequence) == 0) {
        i = ZAPPY->tick->nb_ticks / (30 * ZAPPY->frequence);
        printf("%s: %d minutes and %d seconds\n", INFO,
        (i % 2 == 0 ? i / 2 : (i - 1) / 2), (i % 2 == 0 ? 0 : 30));
        display_levels(server, false);
    }
    display_clock_terminal(ZAPPY);
}

/// @brief Check if the ticks have to be updated and call functions
/// @param server Structure that contain all server data
/// @param tick Structure that contain all tick data
/// @param elapsed_time Time before the last tick
static void handle_tick(server_t *server, tick_t *tick,
    struct timeval *elapsed_time)
{
    int ret = 0;

    if (elapsed_time->tv_sec >= 1 || (elapsed_time->tv_sec == 0 &&
        elapsed_time->tv_usec >= tick->tick)) {
        ret = gettimeofday(&tick->last_time, NULL);
        if (ret == -1)
            return perror("handle tick");
        ret = pthread_mutex_lock(&tick->mutex_tick);
        if (ret != 0)
            return perror("handle tick");
        tick->nb_ticks += 1;
        ret = pthread_mutex_unlock(&tick->mutex_tick);
        if (ret != 0)
            return perror("handle tick");
        check_game_condition(server);
        check_command_vector(server);
        display_tick_info(server);
    }
}

/// @brief Handle the compute of ticks
/// @param server Structure that contain all server data
/// @return NULL
void *compute_tick(void *server)
{
    server_t *tmp = (server_t *)server;
    tick_t *tick = tmp->zappy->tick;
    struct timeval current_time;
    struct timeval elapsed_time;
    int ret = 0;

    while (tick->is_threading) {
        ret = gettimeofday(&current_time, NULL);
        if (ret == -1)
            perror("compute_tick");
        timersub(&current_time, &tick->last_time, &elapsed_time);
        handle_tick(tmp, tick, &elapsed_time);
    }
    pthread_join(tick->thread, NULL);
    return NULL;
}
