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
    static std::string buffer;
    std::string delimiter = "\n";
    std::string serverResponse;
    size_t pos = 0;

    fd >> serverResponse;
    buffer.append(serverResponse);
    while ((pos = buffer.find(delimiter)) != std::string::npos) {
        std::string response = buffer.substr(0, pos);
        buffer.erase(0, pos + delimiter.length());
        std::cout << "response -> " << response << std::endl;
        handleCommand(response, fd);
    }
}

void Zappy::AI::handleCommand(std::string response, int fd)
{
    if (response == "WELCOME")
        fd << (_teamName + "\n");
    if (response == "dead") {
        _isAlive = false;
        _clientSocket->~Socket();
    }
    //TODO faire l'algo ici
}
