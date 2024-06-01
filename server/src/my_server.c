/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** Server
*/

#include "../include/server.h"

server_t *server;

/// @brief Set an address on a default IP to a given port
/// @param port Port of the address
struct sockaddr_in set_address(int port)
{
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    return address;
}

/// @brief Set an address and a Socket to the given port, then bind them
/// @param server Structure that contain all server data
/// @param port Port of the address
static void config_control(server_t *server, int port)
{
    int socket_opt = 1;

    server->ctrl_addr = set_address(port);
    setsockopt(FD_CTRL, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &socket_opt\
    , sizeof(socket_opt));
    bind(FD_CTRL, (struct sockaddr*)&ADDR_CTRL, sizeof(ADDR_CTRL));
}

/// @brief Initialize a default server
/// @return Server structure with default values
static server_t *init_server(void)
{
    server_t *server = malloc(sizeof(server_t));

    server->control_fd = socket(AF_INET, SOCK_STREAM, 0);
    server->nb_client = 0;
    server->clients = NULL;
    return server;
}

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
    close(FD_CTRL);
    free_zappy(server->zappy);
    free_clients(server);
    close(server->control_fd);
    free(server);
}

/// @brief Server loop that allow new client connexion and add it to the server
/// @param server Structure that contain all server data
void add_client_loop(server_t *server)
{
    int tmp = 0;
    int client_fd = 0;
    fd_set fd;
    socklen_t addrlen = sizeof((struct sockaddr*)&ADDR_CTRL);
    struct timeval time;

    time.tv_sec = 0;
    time.tv_usec = 100000;
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

/// @brief Server loop that read client already connected
/// @param server Structure that contain all server data
void read_client_loop(server_t *server)
{
    int tmp = 0;
    fd_set fd;
    struct timeval time;

    time.tv_sec = 0;
    time.tv_usec = 100000;
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

/// @brief Initialize a server with Zappy information and start it
/// @param zappy Structure that contains all games information
/// @return 0 if the server was created with success, else returns 84
int my_server(zappy_t *zappy)
{
    server = init_server();
    if (server->control_fd == -1) {
        RAISE("No socket available\n");
        free_server(server);
        return 84;
    }
    server->zappy = zappy;
    signal(SIGINT, teams_sigint);
    config_control(server, zappy->port);
    listen(server->control_fd, NB_MAX_CLIENT);
    while (server != NULL) {
        add_client_loop(server);
        if (server != NULL)
            read_client_loop(server);
    }
    return 0;
}
