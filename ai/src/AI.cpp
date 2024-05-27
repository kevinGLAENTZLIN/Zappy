/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AI.cpp
*/

#include "AI.hpp"
#include "Utils/Socket.hpp"
#include <memory>

Zappy::AI::AI(const std::string port, const std::string teamName, const std::string ip)
{
    _port = port;
    _ip = ip;
    _teamName = teamName;
    _clientSocket = std::make_unique<Zappy::Socket>();
    _isAlive = true;
}

void Zappy::AI::run(void)
{
    _clientSocket->connectSocket(_port, _ip);
    std::string test = "test\n";
    std::string response;
    int fd = 0;

    while (_isAlive) {
        _clientSocket->selectSocket();
        fd = _clientSocket->getSocket();
        fd << test;
        fd >> response;
        std::cout << response << std::endl;
    }
}
