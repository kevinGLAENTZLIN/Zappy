/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Server
*/

#include "../../include/server.h"

server_t *server;

/// @brief Free all clients of the given server
/// @param server Structure that contain all server data
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

/// @brief Free the given server
/// @param server Structure that contain all server data
void free_server(server_t *server)
{
    int ret = 0;

    ret = close(FD_CTRL);
    if (ret == -1)
        perror("free_server");
    free_zappy(server->zappy);
    free_clients(server);
    free(server);
}

/// @brief Server loop that allow new client connection and add it to the
/// server
/// @param server Structure that contain all server data
void add_client_loop(server_t *server, struct timeval *timeout)
{
    int tmp = 0;
    int client_fd = 0;
    fd_set fd;
    socklen_t addrlen = sizeof((struct sockaddr*)&ADDR_CTRL);

    if (server->nb_client + 1 >= NB_MAX_CLIENT)
        return;
    FD_ZERO(&fd);
    FD_SET(FD_CTRL, &fd);
    tmp = select(FD_CTRL + 1, &fd, NULL, NULL, timeout);
    if (tmp == -1)
        return perror("add_client_loop");
    if (tmp == 1) {
        client_fd = accept(FD_CTRL, (struct sockaddr*)&ADDR_CTRL, &addrlen);
        if (client_fd == -1)
            return perror("add_client_loop");
        add_client(server, client_fd);
    }
}

/// @brief Server loop that read client already connected
/// @param server Structure that contain all server data
static void read_client_loop(server_t *server, struct timeval *timeout, int i)
{
    int tmp = 0;
    fd_set fd;
    client_t *client = NULL;

    client = CLIENT;
    if (client == NULL)
        return;
    FD_ZERO(&fd);
    FD_SET(client->fd, &fd);
    tmp = select(client->fd + 1, &fd, NULL, NULL, timeout);
    if (tmp == -1) {
        return perror("read_client_loop");
    } else if (tmp == 1) {
        read_client(server, i);
    }
}

/// @brief Call the function to add and read Clients
/// @param server Structure that contain all server data
static void server_loop_call(server_t *server, struct timeval *timeout)
{
    if (server != NULL && server->nb_client == 0)
        return add_client_loop(server, NULL);
    if (server != NULL) {
        add_client_loop(server, timeout);
    }
    if (server != NULL) {
        for (int i = 0; i < server->nb_client; i++) {
            read_client_loop(server, timeout, i);
        }
    }
}

/// @brief Initialize a server with Zappy information and start it
/// @param server Structure that contains all games information
/// @return 0 if the server was created with success, else returns 84
static int my_server2(server_t *server)
{
    int tmp = 0;

    tmp = listen(server->control_fd, NB_MAX_CLIENT);
    if (tmp == -1) {
        perror("my_server");
        return 84;
    }
    printf("%s: Server started\n", INFO);
    pthread_create(&ZAPPY->tick->thread, NULL, &compute_tick, server);
    while (server != NULL)
        server_loop_call(server, &(struct timeval){0, TIMEOUT});
    return 0;
}

/// @brief Initialize a server with Zappy information and start it
/// @param zappy Structure that contains all games information
/// @return 0 if the server was created with success, else returns 84
int my_server(zappy_t *zappy)
{
    void (*ret)(int);

    if (zappy == NULL)
        return 84;
    server = init_server();
    if (server->control_fd == -1) {
        RAISE("No socket available\n");
        free_server(server);
        return 84;
    }
    server->zappy = zappy;
    ret = signal(SIGINT, teams_sigint);
    if (ret == SIG_ERR)
        perror("my_server");
    config_control(server, zappy->port);
    return my_server2(server);
}
