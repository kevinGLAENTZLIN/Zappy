/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** command
*/

#include "../include/server.h"

char *get_parameter(char *input, size_t index)
{
    char *str;
    int len = 0;

    for (; input[index] != '"' && input[index] != 0; index++);
    if (input[index] == 0 || input[index + 1] == 0)
        return NULL;
    index += 1;
    for (; input[index + len] != '"' && input[index + len] != 0; len++);
    if (input[index + len] == 0)
        return NULL;
    str = malloc(sizeof(char) * (len + 1));
    strncpy(str, &input[index], len);
    str[len] = 0;
    return str;
}

char **get_parameters(char *input)
{
    int count = 0;
    int index = 0;
    int i = 0;
    char **tab;

    for (int i = 0; input[i] != 0; i++)
        if (input[i] == '"')
            count += 1;
    if (count == 0 || count % 2 == 1)
        return NULL;
    tab = malloc(sizeof(char *) * (count / 2 + 1));
    for (; i < count / 2; i++) {
        for (; input[index] != '"' && input[index] != 0; index++);
        tab[i] = get_parameter(input, index);
        if (tab[i] != NULL)
            index += strlen(tab[i]) + 2;
    }
    tab[i] = NULL;
    return tab;
}

void free_tab(char **tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

int my_len(void *delimiter, void **elts)
{
    int i = 0;

    if (elts == delimiter)
        return 0;
    for (; elts[i] != delimiter; i++);
    return i;
}

static int command_loop_handling(char **list_cmd, void (**list_func)(),
    server_t *server, int i)
{
    void (*command)();

    for (int j = 0; j < my_len(NULL, (void **)list_cmd); j++) {
        if (strncmp(BUFF_CLIENT, list_cmd[j], strlen(list_cmd[j])) == 0) {
            command = list_func[j];
            command(server, i, BUFF_CLIENT);
            return 1;
        }
    }
    return 0;
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
    dprintf(FD_CLIENT, "ko\n");
}
