/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** command
*/

#include "../include/server.h"

/// @brief Server command interpreter
/// @param list_cmd Command's list handled by the interpreter
/// @param list_func Function's list corresponding to the Command's list
/// @param server Structure that contain all server data
/// @param i Index of the Client
/// @return True if it execute a command, else returns False
static bool command_loop_handling(char **list_cmd, void (**list_func)(),
    server_t *server, int i)
{
    void (*command)();

    for (int j = 0; j < my_len(NULL, (void **)list_cmd); j++) {
        if (strncmp(CMD_CLIENT, list_cmd[j], strlen(list_cmd[j])) == 0) {
            command = list_func[j];
            command(server, i, CMD_CLIENT);
            return true;
        }
    }
    return false;
}

/// @brief Set the Client as an AI
/// @param server Structure that contain all server data
/// @param i Index of the Client
static void set_client_ia_mode(server_t *server, int i)
{
    client_t *client = CLIENT;
    team_t *team = get_team_by_name(server, client->cmds->command);
    egg_t *egg = get_random_egg(server, team);
    player_t *player = init_player(egg->x, egg->y);

    hatch_egg(server, egg);
    client->client_type = strdup(IA);
    client->player_id = team->nb_player;
    client->team_name = strdup(team->team_name);
    client->player = player;
    push_back_player(team, player, server);
    dprintf(client->fd, "%d\n", team->nb_max_player - team->nb_player);
    dprintf(client->fd, "%d %d\n", player->x, player->y);
    // send_to_all_gui(server, "ebo #%d\n", egg->id); // Todo Fix Valgrind
    send_to_all_gui(server, "pnw #%d %d %d %d %d %s\n", player->id, player->x,
    player->y, player->direction + 1, player->level + 1, player->team_name);
}

/// @brief Check and connect client if necessary
/// @param server Structure that contain all server data
/// @param i Index of the Client
/// @return Return True if it connected, else False
static bool check_connection_command(server_t *server, int i)
{
    if (CLIENT_TYPE != NULL)
        return false;
    if (strncmp(CMD_CLIENT, GUI, strlen(GUI)) == 0) {
        CLIENT_TYPE = strdup(GUI);
        return true;
    }
    if (is_team_name(server, CMD_CLIENT)) {
        set_client_ia_mode(server, i);
        return true;
    }
    dprintf(FD_CLIENT, "Invalid Client Type\n");
    return false;
}

/// @brief Server command interpreter
/// @param server Structure that contain all server data
/// @param i Index of the Client
void command_handling(server_t *server, int i)
{
    char *list_gui_cmd[] = {"msz", "bct", "mct", "tna", "ppo", "plv", "pin",
        "sgt", "sst", NULL};
    char *list_ia_cmd[] = {"Forward", "Right", "Left", "Look", "Inventory",
    "Broadcast", "Connect_", "Fork", "Eject", "Take", "Set", "Incantation",
    NULL};
    void (*gui_func[])() = {&msz, &bct, &mct, &tna, &ppo, &plv, &pin,
        &sgt, &sst};
    void (*ia_func[])() = {&forward, &my_right, &my_left, &look, &inventory,
        &broadcast, &my_connect, &my_fork, &eject, &take, &set, &incantation};

    if (check_connection_command(server, i) || CLIENT_TYPE == NULL)
        return;
    if (strcmp(CLIENT_TYPE, GUI) == 0 &&
    command_loop_handling(list_gui_cmd, gui_func, server, i))
        return;
    if (strcmp(CLIENT_TYPE, GUI) != 0 &&
    command_loop_handling(list_ia_cmd, ia_func, server, i))
        return;
    dprintf(FD_CLIENT, (strcmp(CLIENT_TYPE, GUI) == 0 ? "suc\n" : "ko\n"));
}
