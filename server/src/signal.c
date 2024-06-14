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
    printf("\033[1;31m[INFO]\033[0m: Shutting down the server\n");
    server = NULL;
    exit(0);
}
