/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** signal
*/

#include "../include/server.h"

extern server_t *server;

void teams_sigint(int signum)
{
    (void) signum;
    free_myteams(server);
    server = NULL;
    exit(0);
}
