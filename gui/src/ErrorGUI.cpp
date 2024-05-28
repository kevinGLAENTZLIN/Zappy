/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ErrorGUI.cpp
*/

#include "ErrorGUI.hh"
#include <system_error>

Zappy::ErrorGUI::ErrorGUI(const std::string &error)
{
    if (!error.empty()) {
        _msg = error;
    } else {
        _msg = "Error";
    }
}

Zappy::ErrorGUI::ErrorGUI(ErrorType error)
{
    switch (error) {
        case SocketError:
            _msg = "Socket error";
            break;
        case ArgError:
            _msg = "Argument error";
            break;
        default:
            _msg = "Unknown error";
            break;
    }
}

Zappy::ErrorGUI::ErrorGUI(ErrorType error, const std::string &msg)
{
    switch (error) {
        case SocketError:
            _msg = "Socket error: " + msg;
            break;
        case ArgError:
            _msg = "Argument error: " + msg;
            break;
        default:
            _msg = "Unknown error";
            break;
    }
}

const char *Zappy::ErrorGUI::what() const noexcept
{
    return _msg.c_str();
}
