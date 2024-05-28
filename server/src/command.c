/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** command
*/

#include "../include/server.h"

static bool command_loop_handling(char **list_cmd, void (**list_func)(),
    server_t *server, int i)
{
    void (*command)();

    for (int j = 0; j < my_len(NULL, (void **)list_cmd); j++) {
        if (strncmp(BUFF_CLIENT, list_cmd[j], strlen(list_cmd[j])) == 0) {
            command = list_func[j];
            command(server, i, BUFF_CLIENT);
            return true;
        }
    }
    return false;
}

static bool check_connexion_command(server_t *server, int i)
{
    if (CLIENT_TYPE != NULL)
        return false;
    if (strncmp(BUFF_CLIENT, GUI, strlen(GUI)) == 0) {
        CLIENT_TYPE = strdup(GUI);
        return true;
    }
    if (is_team_name(server, BUFF_CLIENT)) {
        CLIENT_TYPE = strdup(TEAM);
        return true;
    }
    return false;
}

void command_handling(server_t *server, int i)
{
    char *list_gui_cmd[] = {"msz", "bct", "mct", "tna", "ppo", "plv", "pin",
        "sgt", "sst", NULL};
    char *list_ia_cmd[] = {"Forward", "Right", "Left", "Look", "Inventory",
    "Broadcast", "Connect_", "Fork", "Eject", "Take", "Set", "Incantation",
    NULL};
    void (*gui_func[])() = {&msz, &bct, &mct, &tna, &ppo, &plv, &pin,
        &sgt, &sst};
    void (*ia_func[])() = {&forward, &right, &left, &look, &inventory,
        &broadcast, &my_connect, &my_fork, &eject, &take, &set, &incantation};

    if (command_loop_handling(list_gui_cmd, gui_func, server, i))
        return;
    if (command_loop_handling(list_ia_cmd, ia_func, server, i))
        return;
    if (check_connexion_command(server, i))
        return;
    dprintf(FD_CLIENT, "ko\n");
}
