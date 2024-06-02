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

static void free_command(command_t *tmp)
{
    free(tmp->command);
    free(tmp);
}

void free_commands(client_t *client)
{
    command_t *tmp = client->cmds;

    if (tmp == NULL)
        return;
    client->cmds = tmp->next;
    free_command(tmp);
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

static void pull_front(client_t *client)
{
    command_t *tmp = client->cmds;

    if (tmp == NULL)
        return;
    client->cmds = tmp->next;
    free_command(tmp);
}

static void exec_client_command(server_t *server, int i)
{
    command_handling(server, i);
    pull_front(CLIENT);
}

static void check_action_message(server_t *server, client_t *client)
{
    if (client->ai_action_message != NULL) {
        dprintf(client->fd, client->ai_action_message);
        free(client->ai_action_message);
        client->ai_action_message = NULL;
    }
    if (client->gui_action_message != NULL) {
        send_to_all_gui(server, client->gui_action_message);
        free(client->gui_action_message);
        client->gui_action_message = NULL;
    }
}

void check_command_vector(server_t *server)
{
    for (int i = 0; i < server->nb_client; i++) {
        if (CLIENT->time_to_wait == 0)
            check_action_message(server, CLIENT);
        if (CLIENT->time_to_wait == 0 && CLIENT->cmds != NULL)
            return exec_client_command(server, i);
        if (CLIENT->time_to_wait > 0)
            CLIENT->time_to_wait -= 1;
    }
}
