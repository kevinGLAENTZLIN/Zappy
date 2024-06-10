/*
** EPITECH PROJECT, 2024
** Zappy : Server
** File description:
** main
*/

#include "../include/server.h"

/// @brief Return if the string contains only digit
/// @param str Inspected string
/// @return True if string contains only digit, else false
int is_number(char *str)
{
    if (str == NULL)
        return false;
    for (int i = 0; str[i] != 0 && str[i] != '\r'; i++)
        if (str[i] > '9' || str[i] < '0')
            return false;
    return true;
}

/// @brief Write in the error output the given string and the errno message
/// @param str Error message
/// @return NULL
void *my_perror(char *str)
{
    perror(str);
    return NULL;
}

/// @brief Display help message
void print_help(void)
{
    int r = 0;

    r = MIN(printf("\nUSAGE: ./zappy_server -p port -x width -y height -n "),
    r);
    r = MIN(printf("name1 name2 ... -c clientsNb -f freq\n\n"), r);
    r = MIN(printf("\t-p port \t\tPort Number\n"), r);
    r = MIN(printf("\t-x width\t\tWidth of the world\n"), r);
    r = MIN(printf("\t-y height\t\tHeight of the world\n"), r);
    r = MIN(printf("\t-n name1 name2...\tname of the team\n"), r);
    r = MIN(printf("\t-c clientsNB\t\tNumber of authorized clients per team\n")
    , r);
    r = MIN(printf("\t-f freq \t\tReciprocal of time unit for execution"), r);
    r = MIN(printf(" of actions\n\n"), r);
    if (r < 0) {
        perror("print_help");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

/// @brief Argument error handling
/// @param argc Total number of arguments
/// @param argv Arguments list
/// @return Return True if there is an error, else False
static int check_flags(int argc, char **argv)
{
    int score = 1;

    if (argc < 11)
        return 1;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0)
            score *= 2;
        if (strcmp(argv[i], "-n") == 0)
            score *= 3;
        if (strcmp(argv[i], "-x") == 0)
            score *= 5;
        if (strcmp(argv[i], "-y") == 0)
            score *= 7;
        if (strcmp(argv[i], "-p") == 0)
            score *= 11;
        if (strcmp(argv[i], "-f") == 0)
            score *= 13;
    }
    return (score == 2310 || score == 30030) ? 0 : 1;
}

/// @brief Argument error handling
/// @param argc Total number of arguments
/// @param argv Arguments list
/// @return Return True if there is an error, else False
static int error_handling(int argc, char **argv)
{
    bool tmp = false;

    for (int i = 1; i < argc; i++) {
        if (!tmp && argv[i][0] != '-')
            return 1;
        if (tmp && argv[i][0] == '-')
            tmp = false;
        if (tmp && strcmp(argv[i], "GRAPHICAL") == 0)
            return 1;
        if (!tmp && strcmp(argv[i], "-n") == 0 && i + 1 < argc &&
        argv[i + 1][0] != '-')
            tmp = true;
        if (!tmp && argv[i][0] == '-' && i + 1 == argc)
            return 1;
        if (!tmp && argv[i][0] == '-' && !is_number(argv[i + 1]))
            return 1;
        if (!tmp && argv[i][0] == '-' && is_number(argv[i + 1]))
            i += 1;
    }
    return (check_flags(argc, argv) ? true : false);
}

/// @brief Start a server to play the Zappy game
/// @param argc Total number of arguments
/// @param argv Arguments list
/// @return Return 0 if the server start successfully, else 84
int main(int argc, char **argv)
{
    if (argc == 2 && (strcmp(argv[1], "-help") == 0 ||
    strcmp(argv[1], "-h") == 0)) {
        print_help();
    }
    if (error_handling(argc, argv)) {
        RAISE("Argument error\n");
        return 84;
    }
    srand(time(NULL));
    return my_server(check_zappy(init_zappy(argc, argv)));
}
