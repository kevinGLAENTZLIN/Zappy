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
    free_server(server);
    server = NULL;
    exit(0);
}
