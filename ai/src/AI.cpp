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
}

void Zappy::AI::checkArg(int argc, char **argv)
{
    if (argc != 7) {
        throw Zappy::ErrorAI(ArgError, "invalid number of arguments");
    }
    if (std::string(argv[1]) != "-p" || std::string(argv[3]) != "-n" ||
        std::string(argv[5]) != "-h") {
        throw Zappy::ErrorAI(ArgError, "-p or -n or -h missing, check -h");
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
    _numberCmdInQueue = 1;
    _food = 9;
    _numberCmdInQueue = 0;
    _commandQueue.push("Inventory\n");
}

void Zappy::AI::run(void)
{
    int fd = 0;
    _clientSocket->connectSocket(_port, _ip);
    fd = _clientSocket->getSocket();

    while (_isAlive) {
        if (_clientSocket->selectSocket() == -1) {
            handleResponse(fd);
        } else if (_numberCmdInQueue < 10) {
            handleDefaultAction(fd);
        }
    }
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
    _numberCmdInQueue--;
    if (response == "WELCOME") {
        fd << (_teamName + "\n");
    } else if (response == "dead") {
        _isAlive = false;
        _clientSocket->~Socket();
    } else {
        handlePriority(response, fd);
    }
}

void Zappy::AI::handlePriority(std::string response, int fd)
{
    if (_lastCommand != "Look\n" && response.find("[") != std::string::npos)
        parseInventory(response);
    if (_food <= 2) {
        std::string fork = "Fork\n";
        fd << fork;
        _numberCmdInQueue++;
    }
    if (_food > 2) {
        std::cout << "Food > 2" << std::endl;
        _commandQueue.push("Forward\n");
        _commandQueue.push("Right\n");
        _commandQueue.push("Look\n");
        _commandQueue.push("Inventory\n");
    }
}

void Zappy::AI::handleDefaultAction(int fd)
{
    if (!_commandQueue.empty() && _food > 2) {
        std::string command = _commandQueue.front();
        std::cout << "commande faite -> " << command;
        _commandQueue.pop();
        _lastCommand = command;
        fd << command;
        _numberCmdInQueue++;
    }
}

void Zappy::AI::parseInventory(const std::string &response)
{
    std::istringstream stream(response);
    std::string stringFind;

    while (stream >> stringFind) {
        if (stringFind == "food") {
            stream >> _food;
        } else if (stringFind == "linemate") {
            stream >> _linemate;
        } else if (stringFind == "deraumere") {
            stream >> _deraumere;
        } else if (stringFind == "sibur") {
            stream >> _sibur;
        } else if (stringFind == "mendiane") {
            stream >> _mendiane;
        } else if (stringFind == "phiras") {
            stream >> _phiras;
        } else if (stringFind == "thystame") {
            stream >> _thystame;
        }
    }
}