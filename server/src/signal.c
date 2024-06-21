/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** signal
*/

#include "../include/server.h"

extern server_t *server;

/// @brief Redirect Ctrl-C Signal in order to free the Server structure
void teams_sigint(int signum)
{
    (void) signum;
    ZAPPY->tick->is_threading = false;
    printf("\n%s: Tick %d\n", INFO, ZAPPY->tick->nb_ticks);
    display_levels(server, true);
    free_server(server);
    printf("%s: Shutting down the server\n", INFO);
    server = NULL;
    exit(0);
}
