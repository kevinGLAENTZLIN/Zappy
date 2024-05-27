/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main.cpp
*/

#include <iostream>
#include "ErrorAI.hpp"
#include "AI.hpp"

static int printHelp(void)
{
    std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
    return 0;
}

static int errorHandling(int argc , char **argv)
{
    if (argc != 7) {
        std::cerr << "Invalid number of arguments" << std::endl;
        return 84;
    }
    if (std::string(argv[1]) != "-p" || std::string(argv[3]) != "-n" ||
        std::string(argv[5]) != "-h") {
        std::cerr << "Invalid arguments" << std::endl;
        return 84;
    }
}

int main(int argc, char **argv)
{
    if (argc == 2 && std::string(argv[1]) == "-help") {
        return printHelp();
    if (errorHandling(argc, argv) == 84)
        return 84;
    try {
        Zappy::AI ai(argv[2], argv[4], argv[6]);
        ai.run();
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
