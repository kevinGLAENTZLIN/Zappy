/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** client
*/

#include "../include/server.h"

/// @brief Initialize a default Client with the given File Descriptor
/// @param fd File Descriptor corresponding to the Client Socket
/// @return Initialized Client
static client_t *init_client(int fd)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        return (client_t *)my_perror("init_client");
    client->fd = fd;
    client->buffer = NULL;
    client->client_type = NULL;
    client->team_name = NULL;
    client->next = NULL;
    client->player = NULL;
    client->player_id = -1;
    client->cmds = NULL;
    client->time_to_wait = 0;
    client->gui_action_message = NULL;
    client->ai_action_message = NULL;
    return client;
}

/// @brief Free the given Client
void free_client(client_t *client)
{
    int ret = 0;

    if (client == NULL)
        return;
    free_commands(client);
    if (client->buffer != NULL)
        free(client->buffer);
    if (client->team_name != NULL)
        free(client->team_name);
    if (client->ai_action_message != NULL)
        free(client->ai_action_message);
    if (client->gui_action_message != NULL)
        free(client->gui_action_message);
    if (client->client_type != NULL)
        free(client->client_type);
    if (client->fd != 0)
        ret = close(client->fd);
    if (ret == -1)
        perror("free_client");
    free(client);
}

/// @brief Returns the pointer of the Nth Client in the Server client
/// linked list
/// @param server Structure that contain all server data
/// @param i Index of the Client
/// @return NULL if not corresponding client or the pointer of the Client
client_t *get_client_by_index(server_t *server, int i)
{
    client_t *tmp = server->clients;

    if (i > server->nb_client || tmp == NULL)
        return NULL;
    for (int j = 0; j < i && tmp->next != NULL; j++)
        tmp = tmp->next;
    return tmp;
}

/// @brief Add a new Client with the given File Descriptor
/// @param server Structure that contain all server data
/// @param fd File Descriptor corresponding to the Client Socket
void add_client(server_t *server, int fd)
{
    client_t *tmp = server->clients;

    if (tmp == NULL) {
        server->clients = init_client(fd);
        send_client(server->clients->fd, "WELCOME\n");
    } else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = init_client(fd);
        send_client(tmp->next->fd, "WELCOME\n");
    }
    server->nb_client += 1;
}

/// @brief Read the given Client command
/// @param server Structure that contain all server data
/// @param i Index of the Client
void read_client(server_t *server, int i)
{
    client_t *client = CLIENT;

    if (client == NULL)
        return;
    client->buffer = read_to_buffer(client->fd, '\n');
    if (client->buffer == NULL)
        return disconnect_client(server, client);
    if (!is_in_str('\n', client->buffer)) {
        free(client->buffer);
        client->buffer = NULL;
    }
    if (client->buffer != NULL) {
        push_back_command(server, i);
        free(client->buffer);
        client->buffer = NULL;
    }
}

/// @brief Disconnect the given Client from the given Server and free it
/// @param server Structure that contain all server data
/// @param client Client to disconnect
void disconnect_client(server_t *server, client_t *client)
{
    client_t *tmp = server->clients;

    if (tmp == client) {
        server->nb_client -= 1;
        server->clients = client->next;
        free_client(client);
        return;
    }
    while (tmp->next != NULL) {
        if (tmp->next == client) {
            server->nb_client -= 1;
            tmp->next = client->next;
            free_client(client);
            return;
        }
        tmp = tmp->next;
    }
}
