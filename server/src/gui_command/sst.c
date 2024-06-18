/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** sst
*/

#include "../../include/server.h"

/// @brief Sst command of the GUI protocol
/// @param server Structure that contains all games information
/// @param i Index of the Client
/// @param input Command input from the Client
void sst(server_t *server, int i, char *input)
{
    char **tab = get_parameters(input);
    int tmp = ZAPPY->frequence;

    if (tab == NULL || is_number(tab[0])) {
        free_tab(tab);
        return (void)send_client(FD_CLIENT, "sbp\n");
    }
    ZAPPY->frequence = atoi(tab[0]);
    ZAPPY->tick->tick = TICK;
    if (ZAPPY->frequence < 0 || ZAPPY->frequence > 2000)
        ZAPPY->frequence = tmp;
    send_to_all_gui(server, "sst %d\n", ZAPPY->frequence);
    free_tab(tab);
}
