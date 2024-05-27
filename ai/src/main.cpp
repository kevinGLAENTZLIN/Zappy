/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main.cpp
*/

#include <iostream>

static void printHelp(void)
{
    std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc == 2 && std::string(argv[1]) == "-help") {
        printHelp();
        return 0;
    }
}
