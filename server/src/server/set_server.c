/*
** EPITECH PROJECT, 2024
** server
** File description:
** set_server
*/

#include "../../include/server.h"

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
void config_control(server_t *server, int port)
{
    int ret = 0;
    int socket_opt = 1;

    server->ctrl_addr = set_address(port);
    ret = setsockopt(FD_CTRL, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    &socket_opt, sizeof(socket_opt));
    if (ret == -1)
        perror("config_control");
    ret = bind(FD_CTRL, (struct sockaddr*)&ADDR_CTRL, sizeof(ADDR_CTRL));
    if (ret == -1)
        perror("config_control");
}

/// @brief Initialize a default server
/// @return Server structure with default values
server_t *init_server(void)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL)
        return (server_t *)my_perror("init_server");
    server->control_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->control_fd == -1) {
        free(server);
        return (server_t *)my_perror("init_server");
    }
    server->nb_client = 0;
    server->clients = NULL;
    return server;
}
