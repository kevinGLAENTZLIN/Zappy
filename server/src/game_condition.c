/*
** EPITECH PROJECT, 2024
** server
** File description:
** game_condition
*/

#include "../include/server.h"

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

static void check_dead(server_t *server, player_t *player)
{
    client_t *client = NULL;

    if (player == NULL)
        return;
    if (player->food <= 0) {
        client = get_client_by_player(server, player);
        send_to_all_gui(server, "pdi #%d\n", player->id);
        dprintf(client->fd, "U are dead bro\n");
        // Todo Deconnecte et free le client du player
    }
    check_dead(server, player->next);
}

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
        printf("Team %s has won !\n", team->team_name);
        send_to_all_gui(server, "seg %s\n", team->team_name);
    }
}

void check_game_condition(server_t *server)
{
    if (ZAPPY->ticks % 20 == 0)
        set_map_resources(ZAPPY);
    if (ZAPPY->ticks % 126 == 0)
        consume_food(server);
    for (int i = 0; ZAPPY->teams_name[i] != NULL; i++) {
        check_dead(server, TEAM->players);
        check_win(server, TEAM);
    }
}
