/*
** EPITECH PROJECT, 2024
** B-YEP-400-MLH-4-1-zappy-kevin1.glaentzlin
** File description:
** zappy
*/

#include "../include/server.h"

/// @brief Returns the numeric value associated with the sent flag
/// @param flag Flag argument to obtain the following value
/// @param argc Total number of arguments
/// @param argv Argument list
/// @return Return -42 if no value or no flag found
static int get_value_by_flag(char *flag, int argc, char **argv)
{
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], flag) == 0 && i + 1 < argc)
            return atoi(argv[i + 1]);
    }
    return -42;
}

/// @brief Set to Zappy->teams_name all names following flag -n
/// @param zappy Structure that contains al games information
/// @param argc Total number of arguments
/// @param argv Arguments list
/// @param i Index of the flag -n
static void get_names(zappy_t *zappy, int argc, char **argv, int i)
{
    int tmp = 0;
    int size = 0;

    tmp = i + 1;
    for (size = i + 1; size < argc && argv[size][0] != '-'; size++);
    zappy->teams_name = malloc(sizeof(char *) * (size - i + 1));
    for (i += 1; i < argc && argv[i][0] != '-'; i++)
        zappy->teams_name[i - tmp] = strdup(argv[i]);
    zappy->teams_name[i - tmp] = NULL;
}

/// @brief Load to Zappy->teams_name all names following flag -n
/// @param zappy Structure that contains all games information
/// @param argc Total number of arguments
/// @param argv Arguments list
static void load_names(zappy_t *zappy, int argc, char **argv)
{
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            get_names(zappy, argc, argv, i);
            return;
        }
    }
    return;
}

/// @brief Set a certain number of egg randomly spread on the Map
/// @param zappy Structure that contains all games information
static void set_teams_egg(zappy_t *zappy)
{
    for (int j = 0; zappy->teams_name[j] != NULL; j++)
        set_n_random_egg(zappy, zappy->teams[j], zappy->team_size);
}

/// @brief Initialize Zappy following arguments
/// @param argc Total number of arguments
/// @param argv Arguments list
/// @return Zappy that contains all games information
zappy_t *init_zappy(int argc, char **argv)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));

    zappy->x = get_value_by_flag("-x", argc, argv);
    zappy->y = get_value_by_flag("-y", argc, argv);
    zappy->frequence = get_value_by_flag("-f", argc, argv);
    zappy->port = get_value_by_flag("-p", argc, argv);
    zappy->team_size = get_value_by_flag("-c", argc, argv);
    zappy->map = NULL;
    zappy->eggs = NULL;
    zappy->ticks = 0;
    load_names(zappy, argc, argv);
    load_zappy_teams(zappy);
    if (zappy->frequence == -42)
        zappy->frequence = 100;
    init_map(zappy);
    set_map_ressources(zappy);
    set_teams_egg(zappy);
    return zappy;
}

/// @brief Free Zappy structures
/// @param zappy Structure that contains all games information
void free_zappy(zappy_t *zappy)
{
    if (zappy == NULL)
        return;
    free_teams(zappy);
    free_map(zappy);
    free_eggs(zappy->eggs);
    free_tab(zappy->teams_name);
    free(zappy);
}
