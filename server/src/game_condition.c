/*
** EPITECH PROJECT, 2024
** server
** File description:
** game_condition
*/

#include "../include/server.h"

/// @brief Consume one food to each player
/// @param server Structure that contain all server data
static void consume_food(server_t *server)
{
    player_t *tmp = NULL;

    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        tmp = TEAM->players;
        while (tmp != NULL) {
            tmp->food -= 1;
            tmp = tmp->next;
        }
    }
}

/// @brief Check if there is dead player in the given player list
/// @param server Structure that contain all server data
/// @param player Linked list of player
static void check_dead(server_t *server, player_t *player)
{
    client_t *client = NULL;
    player_t *next = NULL;

    if (player == NULL)
        return;
    next = player->next;
    if (player != NULL && player->food <= 0) {
        client = get_client_by_player(server, player);
        if (client == NULL || player == NULL)
            return check_dead(server, next);
        send_to_all_gui(server, "pdi #%d\n", player->id);
        send_client(client->fd, "dead\n");
        printf("\033[A\r");
        printf("%s: Player %d passed away\n", INFO, player->id);
        ZAPPY->clear_line = false;
        disconnect_client(server, get_client_by_player(server, player));
    }
    check_dead(server, next);
}

/// @brief Check if the given team won
/// @param server Structure that contain all server data
/// @param team Concerned team
static void check_win(server_t *server, team_t *team)
{
    player_t *player = team->players;
    int count = 0;

    if (team->nb_player < 6)
        return;
    while (player != NULL) {
        count += (player->level == NB_MAX_LVL);
        player = player->next;
    }
    if (count >= 6) {
        printf("\033[A\r");
        printf("%s:Team %s has won !\n", INFO, team->team_name);
        ZAPPY->clear_line = false;
        send_to_all_gui(server, "seg \"%s\"\n", team->team_name);
    }
}

/// @brief Call all tick relative function
/// @param server Structure that contain all server data
void check_game_condition(server_t *server)
{
    if (ZAPPY->tick->nb_ticks % 20 == 0)
        set_map_resources(ZAPPY);
    if (ZAPPY->tick->nb_ticks % 126 == 0)
        consume_food(server);
    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        check_dead(server, TEAM->players);
        check_win(server, TEAM);
    }
}
