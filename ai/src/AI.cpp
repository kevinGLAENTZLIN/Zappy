/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AI.cpp
*/

#include "AI.hpp"
#include "Utils/Socket.hpp"
#include <memory>

Zappy::AI::AI(const std::string port, const std::string ip, const std::string teamName)
{
    _ip = ip;
    _teamName = teamName;
    _port = port;
    _clientSocket = std::unique_ptr<Zappy::Socket>();
    _isAlive = true;
}

void Zappy::AI::run(void)
{
    _clientSocket->connectSocket(_port, _ip);
    std::string test = "test\n";
    int fd = 0;

    while (_isAlive) {
        _clientSocket->selectSocket();
        fd = _clientSocket->getSocket();
        fd << test;
    }
}
