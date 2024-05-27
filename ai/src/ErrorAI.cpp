/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ErrorAI.cpp
*/

#include "ErrorAI.hpp"
#include <system_error>

Zappy::ErrorAI::ErrorAI(const std::string &error)
{
    if (!error.empty()) {
        _msg = error;
    } else {
        _msg = "Error";
    }
}

Zappy::ErrorAI::ErrorAI(ErrorType error)
{
    switch (error) {
        case SocketError:
            _msg = "Socket error";
            break;
        default:
            _msg = "Unknown error";
            break;
    }
}

Zappy::ErrorAI::ErrorAI(ErrorType error, const std::string &msg)
{
    switch (error) {
        case SocketError:
            _msg = "Socket error: " + msg;
            break;
        default:
            _msg = "Unknown error";
            break;
    }
}

const char *Zappy::ErrorAI::what() const noexcept
{
    return _msg.c_str();
}
