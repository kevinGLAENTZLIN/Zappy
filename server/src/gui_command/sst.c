/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** sst
*/

#include "../../include/server.h"

void sst(server_t *server, int i, char *input)
{
    char **tab = get_parameters(input);

    if (tab == NULL || is_number(tab[0])) {
        free_tab(tab);
        return (void)send_client(FD_CLIENT, "sbp\n");
    }
    ZAPPY->frequence = atoi(tab[0]);
    send_to_all_gui(server, "sst %d\n", ZAPPY->frequence);
    free_tab(tab);
}
