/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Utils
*/


#pragma once

#include <iostream>
#include <vector>

namespace Zappy {
    class Utils {
    public:
        // INFO: function for the error handling
        static bool isNumber(const std::string &str);
        static bool isIp(const std::string &str);

        // INFO: function for string manipulation
        static std::vector<std::string> split(std::string str, const char &delim);
    private:

    };
}
