/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Server
*/

#include "../include/server.h"

server_t *server_server;

struct sockaddr_in set_address(int port)
{
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    return address;
}

static void config_control(server_t *server, int port)
{
    int socket_opt = 1;

    server->ctrl_addr = set_address(port);
    setsockopt(FD_CTRL, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &socket_opt\
    , sizeof(socket_opt));
    bind(FD_CTRL, (struct sockaddr*)&ADDR_CTRL, sizeof(ADDR_CTRL));
}

static server_t *init_server(void)
{
    server_t *server = malloc(sizeof(server_t));

    server->control_fd = socket(AF_INET, SOCK_STREAM, 0);
    server->nb_client = 0;
    server->clients = NULL;
    return server;
}

static void free_clients(server_t *server)
{
    client_t *tmp = NULL;

    if (server->nb_client <= 0)
        return;
    tmp = server->clients->next;
    free_client(server->clients);
    server->clients = tmp;
    server->nb_client -= 1;
    return free_clients(server);
}

void free_myteams(server_t *server)
{
    close(FD_CTRL);
    free_zappy(server->zappy);
    free_clients(server);
    close(server->control_fd);
    free(server);
}

void add_client_loop(server_t *server)
{
    int tmp = 0;
    int client_fd = 0;
    fd_set fd;
    socklen_t addrlen = sizeof((struct sockaddr*)&ADDR_CTRL);
    struct timeval time;

    time.tv_sec = 0;
    time.tv_usec = 500;
    FD_ZERO(&fd);
    FD_SET(FD_CTRL, &fd);
    tmp = select(FD_CTRL + 1, &fd, NULL, NULL, &time);
    if (tmp == -1) {
        return;
    } else if (tmp == 1) {
        client_fd = accept(FD_CTRL, (struct sockaddr*)&ADDR_CTRL, &addrlen);
        add_client(server, client_fd);
    }
}

void read_client_loop(server_t *server)
{
    int tmp = 0;
    fd_set fd;
    struct timeval time;

    time.tv_sec = 0;
    time.tv_usec = 500;
    for (int i = 0; i < server->nb_client; i++) {
        if (CLIENT == NULL)
            continue;
        FD_ZERO(&fd);
        FD_SET(FD_CLIENT, &fd);
        tmp = select(FD_CLIENT + 1, &fd, NULL, NULL, &time);
        if (tmp == -1)
            return;
        if (tmp == 1)
            read_client(server, i);
    }
}

int my_server(zappy_t *zappy)
{
    server_server = init_server();
    if (server_server->control_fd == -1) {
        RAISE("No socket available\n");
        free_myteams(server_server);
        return 84;
    }
    signal(SIGINT, teams_sigint);
    config_control(server_server, zappy->port);
    listen(server_server->control_fd, NB_MAX_CLIENT);
    while (server_server != NULL) {
        add_client_loop(server_server);
        if (server_server != NULL)
            read_client_loop(server_server);
    }
    return 0;
}
