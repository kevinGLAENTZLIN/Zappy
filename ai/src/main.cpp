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

int main(int argc, char **argv)
{
    if (argc == 2 && std::string(argv[1]) == "-help")
        return printHelp();
    try {
        Zappy::AI ai;

        ai.checkArg(argc, argv);
        ai.initAI(argv[2], argv[4], argv[6]);
        ai.run();
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
