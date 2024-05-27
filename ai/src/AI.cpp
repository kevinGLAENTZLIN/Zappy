/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AI.cpp
*/

#include "AI.hpp"
#include "Utils/Socket.hpp"

Zappy::AI::AI()
{
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
}

void Zappy::AI::checkArg(int argc, char **argv)
{
    if (argc != 7) {
        throw Zappy::ErrorAI(ArgError, "invalid number of argument");
    }
    if (std::string(argv[1]) != "-p" || std::string(argv[3]) != "-n" ||
        std::string(argv[5]) != "-h") {
        throw Zappy::ErrorAI(ArgError, "-p or -n or -h missing check -h");
    }
}

void Zappy::AI::initAI(const std::string port, const std::string teamName, const std::string ip)
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
    int fd = 0;

    while (_isAlive) {
        _clientSocket->selectSocket();
        fd = _clientSocket->getSocket();
        handleResponse(fd);
    }
}

void Zappy::AI::handleResponse(int fd)
{
    std::string response = "";

    fd >> response;
    if (response == "WELCOME\n")
        fd << (_teamName + "\n");
    if (response == "dead\n10\n") {
        _isAlive = false;
        _clientSocket->~Socket();
    }
    std::cout << "response -> " << response;
}
