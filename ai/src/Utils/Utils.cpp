/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** utils.cpp
*/

#include "Utils.hh"

extern "C" {
    pid_t Zappy::Utils::process(void)
    {
        pid_t pid = fork();
        return pid;
    }

    bool Zappy::Utils::isInventory(const std::string &response)
    {
        std::istringstream stream(response);
        std::string stringFind;

        stream >> stringFind;
        stringFind = "";
        stream >> stringFind;
        std::cout << "STRING FIND: " << stringFind << std::endl;
        if (stringFind == "food") {
            std::cout << "INVENTORY" << std::endl;
            return true;
        }
        std::cout << "NOT INVENTORY" << std::endl;
        return false;
    }
}