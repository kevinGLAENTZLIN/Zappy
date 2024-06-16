/*
** EPITECH PROJECT, 2024
** server
** File description:
** command_vector
*/

#include "../include/server.h"

/// @brief Initialize a new command
/// @param cmd Command to handle
/// @return Initialized command
static command_t *init_command(char *cmd)
{
    command_t *tmp = malloc(sizeof(command_t));

    if (tmp == NULL)
        return (command_t *)my_perror("init_command");
    tmp->command = strdup(cmd);
    if (tmp->command == NULL)
        return (command_t *)my_perror("init_command");
    tmp->next = NULL;
    return tmp;
}

/// @brief Free the given command
/// @param cmd Command to handle
static void free_command(command_t *cmd)
{
    free(cmd->command);
    free(cmd);
}

/// @brief Free commands of the given Client
void free_commands(client_t *client)
{
    command_t *cmd = client->cmds;

    if (cmd == NULL)
        return;
    client->cmds = cmd->next;
    free_command(cmd);
    free_commands(client);
}

/// @brief Push back a new command, if already 10 commands in the queue
/// the command is not pushed
/// @param server Structure that contain all server data
/// @param i Index of the Client
void push_back_command(server_t *server, int i, char *line)
{
    client_t *client = CLIENT;
    command_t *cmd = client->cmds;
    int count = 1;

    if (cmd == NULL)
        client->cmds = init_command(line);
    else {
        while (cmd->next != NULL) {
            cmd = cmd->next;
            count += 1;
        }
        if (count >= 10) {
            printf("\033[1;31m[INFO]\033[0m: Command %s not added to client"
            " %d\n", line, i);
            return;
        }
        cmd->next = init_command(line);
    }
}

/// @brief Display the command queue of the given Client
/// @param server Structure that contain all server data
/// @param i Index of the Client
void display_command_list(server_t *server, int i)
{
    command_t *cmd = CLIENT->cmds;
    int n = 0;

    while (cmd != NULL) {
        printf("%d: %s", n, cmd->command);
        cmd = cmd->next;
        n += 1;
    }
}

/// @brief Remove the front command of the given Client queue
static void pull_front(client_t *client)
{
    command_t *cmd = client->cmds;

    if (cmd == NULL)
        return;
    client->cmds = cmd->next;
    free_command(cmd);
}

/// @brief Execute and remove the front command
/// @param server Structure that contain all server data
/// @param i Index of the Client
static void exec_client_command(server_t *server, int i)
{
    command_handling(server, i);
    pull_front(CLIENT);
}

/// @brief Display post-action message if necessary
/// @param server Structure that contain all server data
static void check_action_message(server_t *server, client_t *client)
{
    if (client->ai_action_message != NULL) {
        send_client(client->fd, client->ai_action_message);
        free(client->ai_action_message);
        client->ai_action_message = NULL;
    }
    if (client->gui_action_message != NULL) {
        send_to_all_gui(server, client->gui_action_message);
        free(client->gui_action_message);
        client->gui_action_message = NULL;
    }
}

/// @brief Check the command queue and the time to wait before executing next
/// command
/// @param server Structure that contain all server data
void check_command_vector(server_t *server)
{
    client_t *client = NULL;

    for (int i = 0; i < server->nb_client; i++) {
        client = CLIENT;
        if (client->time_to_wait == 0)
            check_action_message(server, client);
        if (client->time_to_wait == 0 && client->cmds != NULL)
            exec_client_command(server, i);
        if (client->time_to_wait > 0)
            client->time_to_wait -= 1;
    }
}
