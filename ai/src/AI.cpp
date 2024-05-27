/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AI.cpp
*/

#include "AI.hpp"
#include "Utils/Socket.hpp"

Zappy::AI::AI(const std::string port, const std::string teamName, const std::string ip)
{
    _port = port;
    _ip = ip;
    _teamName = teamName;
    _clientSocket = std::make_unique<Zappy::Socket>();
    _isAlive = true;
    _commands.push_back("Forward\n");
    _commands.push_back("Right\n");
    _commands.push_back("Left\n");
    _commands.push_back("Look\n");
    _commands.push_back("Inventory\n");
    _commands.push_back("Broadcast text\n");
    _commands.push_back("Connect_nbr\n");
    _commands.push_back("Fork\n");
    _commands.push_back("Eject\n");
    _commands.push_back("Take object\n");
    _commands.push_back("Set object\n");
    _commands.push_back("Incantation\n");
}

Zappy::AI::~AI()
{
    _clientSocket->~Socket();
}

void Zappy::AI::run(void)
{
    _clientSocket->connectSocket(_port, _ip);
    std::string response;
    int fd = 0;

    while (_isAlive) {
        _clientSocket->selectSocket();
        fd = _clientSocket->getSocket();
        fd << _commands[3];
        fd >> response;
        std::cout << response << std::endl;
    }
}
