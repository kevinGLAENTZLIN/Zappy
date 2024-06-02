/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** utils.hh
*/

#pragma once
#include <unistd.h>
#include <string>
#include <sstream>
#include <iostream>

namespace Zappy {

    class Utils {

        public:
            static pid_t process(void);
            static bool isInventory(const std::string &response);
    };

}