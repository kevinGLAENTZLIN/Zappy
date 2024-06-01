/*
** EPITECH PROJECT, 2024
** server
** File description:
** command_vector
*/

#include "../include/server.h"

static command_t *init_command(char *cmd)
{
    command_t *tmp = malloc(sizeof(command_t));

    if (tmp == NULL)
        return NULL;
    tmp->command = strdup(cmd);
    tmp->next = NULL;
    return tmp;
}

void free_commands(client_t *client)
{
    command_t *tmp = client->cmds;

    if (tmp == NULL)
        return;
    client->cmds = tmp->next;
    free(tmp->command);
    free(tmp);
    free_commands(client);
}

void push_back_command(server_t *server, int i)
{
    command_t *tmp = CLIENT->cmds;
    int count = 1;

    if (tmp == NULL)
        CLIENT->cmds = init_command(BUFF_CLIENT);
    else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
            count += 1;
        }
        if (count >= 10)
            return;
        tmp->next = init_command(BUFF_CLIENT);
    }
}

void display_command_list(server_t *server, int i)
{
    command_t *tmp = CLIENT->cmds;
    int n = 0;

    while (tmp != NULL) {
        printf("%d: %s", n, tmp->command);
        tmp = tmp->next;
        n += 1;
    }
}
