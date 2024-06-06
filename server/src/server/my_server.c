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
    ret = close(server->control_fd);
    if (ret == -1)
        perror("free_server");
    free(server);
}

/// @brief Server loop that allow new client connection and add it to the
/// server
/// @param server Structure that contain all server data
void add_client_loop(server_t *server)
{
    int tmp = 0;
    int client_fd = 0;
    fd_set fd;
    socklen_t addrlen = sizeof((struct sockaddr*)&ADDR_CTRL);
    struct timeval time = {0, TIMEOUT};

    FD_ZERO(&fd);
    FD_SET(FD_CTRL, &fd);
    tmp = select(FD_CTRL + 1, &fd, NULL, NULL, &time);
    if (tmp == -1) {
        perror("add_client_loop");
        return;
    }
    if (tmp == 1) {
        client_fd = accept(FD_CTRL, (struct sockaddr*)&ADDR_CTRL, &addrlen);
        if (client_fd == -1)
            return perror("add_client_loop");
        add_client(server, client_fd);
    }
}

/// @brief Server loop that read client already connected
/// @param server Structure that contain all server data
void read_client_loop(server_t *server)
{
    int tmp = 0;
    fd_set fd;
    struct timeval time;
    client_t *client = NULL;

    time.tv_sec = 0;
    time.tv_usec = TIMEOUT;
    for (int i = 0; i < server->nb_client; i++) {
        client = CLIENT;
        if (client == NULL)
            continue;
        FD_ZERO(&fd);
        FD_SET(client->fd, &fd);
        tmp = select(client->fd + 1, &fd, NULL, NULL, &time);
        if (tmp == -1)
            return perror("read_client_loop");
        if (tmp == 1)
            read_client(server, i);
    }
}

static bool server_loop_call(server_t *server)
{
    if (server != NULL)
        add_client_loop(server);
    if (server != NULL)
        read_client_loop(server);
    else
        return false;
    return true;
}

/// @brief Server loop, handle the tick rate
/// @param server Structure that contain all server data
static bool server_loop(server_t *server)
{
    struct timeval current_time;
    struct timeval elapsed_time;
    int ret = 0;

    ret = gettimeofday(&current_time, NULL);
    if (ret == -1)
        perror("server_loop");
    timersub(&current_time, &server->last_tick, &elapsed_time);
    if (elapsed_time.tv_sec >= 1 ||
        (elapsed_time.tv_sec == 0 && elapsed_time.tv_usec >= TICK)) {
        server->zappy->ticks += 1;
        ret = gettimeofday(&server->last_tick, NULL);
        if (ret == -1)
            perror("server_loop");
        check_game_condition(server);
        check_command_vector(server);
    }
    return server_loop_call(server);
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
    tmp = gettimeofday(&server->last_tick, NULL);
    if (tmp == -1) {
        perror("my_server");
        return 84;
    }
    while (server_loop(server));
    return 0;
}

/// @brief Initialize a server with Zappy information and start it
/// @param zappy Structure that contains all games information
/// @return 0 if the server was created with success, else returns 84
int my_server(zappy_t *zappy)
{
    sighandler_t ret;

    if (zappy == NULL)
        return 84;
    server = init_server();
    if (server->control_fd == -1) {
        RAISE("No socket available\n");
        free_server(server);
        return 84;
    }
    srand(time(NULL));
    server->zappy = zappy;
    ret = signal(SIGINT, teams_sigint);
    if (ret == SIG_ERR)
        perror("my_server");
    config_control(server, zappy->port);
    return my_server2(server);
}
