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
