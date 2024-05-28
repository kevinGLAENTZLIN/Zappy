/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** client
*/

#include "../include/server.h"

static client_t *init_client(int fd)
{
    client_t *client = malloc(sizeof(client_t));

    client->fd = fd;
    client->buffer = malloc(sizeof(char) * BUFFER_SIZE);
    client->buffer[0] = 0;
    client->next = NULL;
    return client;
}

void free_client(client_t *client)
{
    if (client == NULL)
        return;
    free(client->buffer);
    if (client->fd != 0)
        close(client->fd);
    free(client);
    client = NULL;
}

client_t *get_client_by_index(server_t *server, int i)
{
    client_t *tmp = server->clients;

    if (i > server->nb_client || tmp == NULL)
        return NULL;
    for (int j = 0; j < i && tmp->next != NULL; j++)
        tmp = tmp->next;
    return tmp;
}

void add_client(server_t *server, int fd)
{
    client_t *tmp = server->clients;

    if (tmp == NULL) {
        server->clients = init_client(fd);
    } else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = init_client(fd);
    }
    server->nb_client += 1;
}

void read_client(server_t *server, int i)
{
    ssize_t size;
    char buffer[BUFFER_SIZE];

    size = read(FD_CLIENT, buffer, BUFFER_SIZE);
    buffer[size] = 0;
    if (size != 0)
        strcat(BUFF_CLIENT, buffer);
    if (strstr(BUFF_CLIENT, "\n") != NULL) {
        printf("Buffer [%s]\n", BUFF_CLIENT);
        command_handling(server, i);
        memset(BUFF_CLIENT, 0, 1024);
    }
}
