/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Utils
*/

#include "Utils.hh"

bool Zappy::Utils::isNumber(const std::string &str)
{
    for (const auto &c : str) {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}

bool Zappy::Utils::isIp(const std::string &str)
{
    std::vector<std::string> ip;

    if (str == "localhost")
        return true;
    ip = Zappy::Utils::split(str, '.');
    if (ip.size() != 4)
        return false;
    for (const auto &octet : ip) {
        if (!Zappy::Utils::isNumber(octet))
            return false;
        if (std::stoi(octet) < 0 || std::stoi(octet) > 255)
            return false;
    }
    return true;
}

std::vector<std::string> Zappy::Utils::split(std::string str, const char &delim)
{
    std::vector<std::string> result;

    while (!str.empty()) {
        std::size_t pos = str.find(delim);
        if (pos == std::string::npos) {
            result.push_back(str);
            break;
        }
        result.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
    }
    return result;
}
