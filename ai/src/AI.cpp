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
    _priorityQueue.push_back("Forward\n");
    _priorityQueue.push_back("Inventory\n");
    _priorityQueue.push_back("Look\n");
    _priorityQueue.push_back("Right\n");
    _priorityQueue.push_back("Fork\n");
    _priorityQueue.push_back("Incantation\n");
    _priorityQueue.push_back("Broadcast\n");
    _priorityQueue.push_back("Connect_nbr\n");
    _priorityQueue.push_back("Eject\n");
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
    _food = 10;
}

void Zappy::AI::initConnection(void)
{
    int nbInstructions = 0;

    _clientSocket->connectSocket(_port, _ip);
    _fd = _clientSocket->getSocket();
    while (true) {
        if (_clientSocket->selectSocket() == -1) {
            std::string response = "";
            _fd >> response;
            if (nbInstructions == 0 && response == "WELCOME\n") {
                _fd << (_teamName + "\n");
            } else if (nbInstructions == 1) {
                std::cout << "Client number -> " << response << std::endl;
            } else if (nbInstructions == 2)
                std::cout << "World size -> " << response << std::endl;
        }
        nbInstructions++;
        if (nbInstructions == 3)
            break;
    }
}

void Zappy::AI::run(void)
{
    std::string serverResponse = "";
    std::cout << "Run AI" << std::endl;
    while (_isAlive) {
        if (_clientSocket->selectSocket() == -1)
            handleResponse();
        else 
            _fd << _priorityQueue[1];
    }
}

void Zappy::AI::handleResponse(void)
{
    std::string serverResponse = "";

    _fd >> serverResponse;
    std::cout << "server response -> " << serverResponse;
    handleCommand(serverResponse);
}

void Zappy::AI::handleCommand(std::string response)
{
    if (response == "dead\n") {
        _isAlive = false;
        _clientSocket->~Socket();
        std::exit(0);
    } else {
        handlePriority(response);
    }
}

void Zappy::AI::handlePriority(std::string response)
{
    if (_food <= 2)
        _fd << _priorityQueue[4];
    if (_food > 2) {
        std::cout << "Food > 2" << std::endl;
        _fd << _priorityQueue[1];
        if (Utils::isInventory(response) && response != "ok\n" && response != "ko\n")
            parseInventory(response);
        if (!Utils::isInventory(response) && response != "ok\n" && response != "ko\n")
            handleLook(response);
    }
}

void Zappy::AI::handleLook(const std::string &response)
{
    std::cout << "Look response -> " << response;
}

void Zappy::AI::parseInventory(const std::string &response)
{
    std::istringstream stream(response);
    std::string stringFind;
    int food = 0;
    int linemate = 0;
    int deraumere = 0;
    int sibur = 0;
    int mendiane = 0;
    int phiras = 0;
    int thystame = 0;

    while (stream >> stringFind) {
        if (stringFind == "food") {
            stream >> food;
        } else if (stringFind == "linemate") {
            stream >> linemate;
        } else if (stringFind == "deraumere") {
            stream >> deraumere;
        } else if (stringFind == "sibur") {
            stream >> sibur;
        } else if (stringFind == "mendiane") {
            stream >> mendiane;
        } else if (stringFind == "phiras") {
            stream >> phiras;
        } else if (stringFind == "thystame") {
            stream >> thystame;
        }
    }

    std::cout << "Food: " << food << std::endl;
    std::cout << "Linemate: " << linemate << std::endl;
    std::cout << "Deraumere: " << deraumere << std::endl;
    std::cout << "sibur " << sibur << std::endl;
    std::cout << "mendiane " << mendiane << std::endl;
    std::cout << "phiras " << phiras << std::endl;
    std::cout << "thystame " << thystame << std::endl;

    if (food < 40)
        _fd << _priorityQueue[2];
}
