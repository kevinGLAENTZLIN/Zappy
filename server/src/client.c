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

    client->fd = fd;
    client->buffer = malloc(sizeof(char) * BUFFER_SIZE);
    client->buffer[0] = 0;
    client->client_type = NULL;
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
    if (client == NULL)
        return;
    free_commands(client);
    free(client->buffer);
    if (client->ai_action_message != NULL)
        free(client->ai_action_message);
    if (client->gui_action_message != NULL)
        free(client->gui_action_message);
    if (client->client_type != NULL)
        free(client->client_type);
    if (client->fd != 0)
        close(client->fd);
    free(client);
    client = NULL;
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
        dprintf(server->clients->fd, "WELCOME\n");
    } else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = init_client(fd);
        dprintf(tmp->next->fd, "WELCOME\n");
    }
    server->nb_client += 1;
}

/// @brief Read the given Client command
/// @param server Structure that contain all server data
/// @param i Index of the Client
void read_client(server_t *server, int i)
{
    client_t *client = CLIENT;
    ssize_t size;
    char buffer[BUFFER_SIZE];

    size = read(client->fd, buffer, BUFFER_SIZE);
    buffer[size] = 0;
    if (size != 0)
        strcat(client->buffer, buffer);
    if (strstr(client->buffer, "\n") != NULL) {
        printf("Buffer [%s]\n", client->buffer);
        push_back_command(server, i);
        display_command_list(server, i);
        memset(client->buffer, 0, 1024);
    }
}
