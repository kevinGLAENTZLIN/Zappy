/*
** EPITECH PROJECT, 2024
** B-YEP-400-MLH-4-1-zappy-kevin1.glaentzlin
** File description:
** server
*/

#pragma once

#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <strings.h>
#include <uuid/uuid.h>
#include <stdbool.h>
#include <math.h>


#define FD_CTRL         server->control_fd
#define ADDR_CTRL       server->ctrl_addr
#define ZAPPY           server->zappy
#define CLIENT          get_client_by_index(server, i)
#define TEAM            ZAPPY->teams[i]
#define MAP             ZAPPY->map

#define TEAM_NAME       TEAM->team_name

#define CLIENT_TYPE     CLIENT->client_type
#define PLAYER          CLIENT->player
#define BUFF_CLIENT     CLIENT->buffer
#define FD_CLIENT       CLIENT->fd
#define PLAYER_TILE     MAP[PLAYER->y][PLAYER->x]

#define GUI             "GRAPHIC"
#define IA              "TEAM"

#define MAX_NAME_LENGTH 32
#define BUFFER_SIZE     1024

#define NB_MAX_LVL      8
#define NB_MAX_CLIENT   42

#define RAISE(x)        write(2, x, strlen(x))

#define SO_REUSEPORT    15

typedef enum direction_e {
    up = 0,
    right,
    down,
    left
} direction_t;

typedef struct tile_s {
    // Todo ? Player ID
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} tile_t;


typedef struct player_s {
    char *team_name;
    int id;
    int x;
    int y;
    int level;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    direction_t direction;
    struct player_s *next;
} player_t;

typedef struct team_s {
    char *team_name;
    int nb_max_player;
    int nb_player;
    player_t *players;
} team_t;

typedef struct client_s {
    int fd;
    char *buffer;
    struct client_s *next;
    char *team_name;
    int player_id;
    char *client_type;
    player_t *player;
} client_t;

typedef struct zappy_s {
    int x;
    int y;
    int frequence;
    int port;
    int team_size;
    char **teams_name;
    team_t **teams;
    tile_t ***map;
    // Todo Tick;
} zappy_t;

typedef struct server_s {
    int control_fd;
    int nb_client;
    zappy_t *zappy;
    struct sockaddr_in ctrl_addr;
    client_t *clients;
} server_t;

// * main.c functions :
int is_number(char *str);

// * my_server.c functions :
int my_server(zappy_t *zappy);
void free_myteams(server_t *server);
struct sockaddr_in set_address(int port);
void teams_sigint(int signum);

// * client.c functions :
void add_client(server_t *server, int fd);
void free_client(client_t *client);
void read_client(server_t *server, int i);
client_t *get_client_by_index(server_t *server, int i);

// * player functions :
player_t *init_player(int x, int y);
void free_player(player_t *player);
void free_players(team_t *team);
void push_back_player(team_t *team, player_t *player);

// * team functions :
void load_zappy_teams(zappy_t *zappy);
void free_teams(zappy_t *zappy);
bool is_team_name(server_t *server, const char *name);
team_t *get_team_by_name(server_t *server, const char *name);

// * map.c functions :
void init_map(zappy_t *zappy);
void set_map_ressources(zappy_t *zappy);

// * Zappy functions :
zappy_t *init_zappy(int argc, char **argv);
void free_zappy(zappy_t *zappy);
void free_map(zappy_t *zappy);

// * command.c functions :
void command_handling(server_t *server, int i);

// * command_util.c functions :
char **get_parameters(char *input);
void free_tab(char **tab);
int my_len(void *delimiter, void **elts);

// * GUI commands functions :
void msz(server_t *server, int i, char *input);
void bct(server_t *server, int i, char *input);
void tna(server_t *server, int i, char *input);
void mct(server_t *server, int i, char *input);
void ppo(server_t *server, int i, char *input);
void pin(server_t *server, int i, char *input);
void plv(server_t *server, int i, char *input);
void sgt(server_t *server, int i, char *input);
void sst(server_t *server, int i, char *input);

// * IA commands functions :
void broadcast(server_t *server, int i, char *input);
void my_connect(server_t *server, int i, char *input);
void eject(server_t *server, int i, char *input);
void my_fork(server_t *server, int i, char *input);
void forward(server_t *server, int i, char *input);
void incantation(server_t *server, int i, char *input);
void inventory(server_t *server, int i, char *input);
void my_left(server_t *server, int i, char *input);
void look(server_t *server, int i, char *input);
void my_right(server_t *server, int i, char *input);
void set(server_t *server, int i, char *input);
void take(server_t *server, int i, char *input);
