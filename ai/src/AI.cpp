/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AI.cpp
*/

#include "AI.hpp"
#include "Utils/Socket.hpp"
#include <queue>
#include <sstream>
#include <thread>

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
    _currentLevel = 1;
    _food = 9;
}

void Zappy::AI::run(void)
{
    int fd = 0;
    _clientSocket->connectSocket(_port, _ip);
    fd = _clientSocket->getSocket();

    while (_isAlive) {
        if (_clientSocket->selectSocket() == -1) {
            handleResponse(fd);
        } else {
            handleDefaultAction(fd);
        }
    }
    std::exit(0);
}

void Zappy::AI::handleResponse(int fd)
{
    std::string buffer;
    std::string delimiter = "\n";
    std::string serverResponse;
    size_t pos = 0;

    fd >> serverResponse;
    std::cout << "server response -> " << serverResponse << std::endl;
    buffer.append(serverResponse);
    while ((pos = buffer.find(delimiter)) != std::string::npos) {
        std::string response = buffer.substr(0, pos);
        buffer.erase(0, pos + delimiter.length());
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
        return;
    }
    handlePriority(response, fd);
}

void Zappy::AI::handlePriority(std::string response, int fd)
{
    //TODO voir le hnadle priority pr regler les boucles inf de inventory
    fd << _commands[4];
    parseInventory(response);

    if (_food < 2) {
        std::cout << "Low food, forking..." << std::endl;
    } else {
        std::cout << "Food level is sufficient." << std::endl;
    }
}


void Zappy::AI::handleDefaultAction(int fd)
{
    std::cout << "handle default action" << std::endl;
    fd << _commands[0];
    fd << _commands[1];
    fd << _commands[3];
}

void Zappy::AI::parseInventory(const std::string &response) {
    std::istringstream stream(response);
    std::string token;
    
    while (stream >> token) {
        if (token == "food") {
            stream >> _food;
        } else if (token == "linemate") {
            stream >> _linemate;
        } else if (token == "deraumere") {
            stream >> _deraumere;
        } else if (token == "sibur") {
            stream >> _sibur;
        } else if (token == "mendiane") {
            stream >> _mendiane;
        } else if (token == "phiras") {
            stream >> _phiras;
        } else if (token == "thystame") {
            stream >> _thystame;
        }
    }
}
