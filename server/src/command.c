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

static void set_client_ia_mode(server_t *server, int i)
{
    team_t *team = get_team_by_name(server, BUFF_CLIENT);
    egg_t *egg = get_random_egg(server, team);
    player_t *player = init_player(egg->x, egg->y);

    hatch_egg(server, egg);
    CLIENT_TYPE = strdup(IA);
    CLIENT->player_id = team->nb_player;
    CLIENT->team_name = strdup(team->team_name);
    PLAYER = player;
    push_back_player(team, player);
    dprintf(FD_CLIENT, "%d\n", team->nb_max_player - team->nb_player);
    dprintf(FD_CLIENT, "%d %d\n", player->x, player->y);
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
        set_client_ia_mode(server, i);
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
    void (*ia_func[])() = {&forward, &my_right, &my_left, &look, &inventory,
        &broadcast, &my_connect, &my_fork, &eject, &take, &set, &incantation};

    if (check_connexion_command(server, i) || CLIENT_TYPE == NULL)
        return;
    if (strcmp(CLIENT_TYPE, GUI) == 0 &&
    command_loop_handling(list_gui_cmd, gui_func, server, i))
        return;
    if (strcmp(CLIENT_TYPE, GUI) != 0 &&
    command_loop_handling(list_ia_cmd, ia_func, server, i))
        return;
    dprintf(FD_CLIENT, "ko\n");
}
