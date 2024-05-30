/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AI.cpp
*/

#include "AI.hpp"

Zappy::AI::AI()
{
    _commands.push_back("Forward\n");
    _commands.push_back("Inventory\n");
    _commands.push_back("Look\n");
    _commands.push_back("Right\n");
    _commands.push_back("Fork\n");
    _commands.push_back("Incantation\n");
    _commands.push_back("Broadcast\n");
    _commands.push_back("Connect_nbr\n");
    _commands.push_back("Eject\n");
    _commands.push_back("Take ");
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
    bool firstRun = true;

    while (_isAlive) {
        if (_clientSocket->selectSocket() == -1)
            handleResponse();
        if (firstRun) {
            sendCommand(_commands[INVENTORY]);
            firstRun = false;
        }
    }
}

void Zappy::AI::handleResponse(void)
{
    std::string serverResponse = "";
    _fd >> serverResponse;

    std::cout << "nbr cmd: " << _numberCmd << std::endl;
    if (!_commandQueue.empty()) {
        std::string command = _commandQueue.front();
        _commandQueue.pop();
        _numberCmd--;
        if (command == "Inventory\n" && serverResponse != "ko\n" && serverResponse != "ok\n") {
            handleInventoryResponse(serverResponse);
        } else if (command == "Look\n" && serverResponse != "ko\n" && serverResponse != "ok\n") {
            handleLookResponse(serverResponse);
        } else if (command == "Take object\n") {
            handleTakeObjectResponse(serverResponse);
        } else {
            handleDefaultResponse(serverResponse);
        }
    }
}

void Zappy::AI::handleLook(const std::string &response)
{
    std::istringstream stream(response);
    std::string tile;
    int tileIndex = 0;

    while (std::getline(stream, tile, ',')) {
        std::istringstream tileStream(tile);
        std::string object;
        while (tileStream >> object) {
            if (object == "food") {
                if (_food < 40) {
                    std::cout << "Pick up food" << std::endl;
                    _fd << _commands[TAKE_OBJECT] + object + "\n";
                    _numberCmd++;
                }
            }
            if (object == "linemate") {
                std::cout << "Move towards linemate" << std::endl;
                _fd << _commands[FORWARD] + object + "\n";
                _numberCmd++;
            }
        }
        tileIndex++;
    }
}

void Zappy::AI::handleInventoryResponse(const std::string &response)
{
    if (Utils::isInventory(response) && response != "ok\n" && response != "ko\n")
        parseInventory(response);
}

void Zappy::AI::handleLookResponse(const std::string &response)
{
    handleLook(response);
}

void Zappy::AI::handleDefaultResponse(const std::string &response)
{
}

void Zappy::AI::handleTakeObjectResponse(const std::string &response)
{
    std::cout << "Take object response: " << response << std::endl;
    if (response == "ok\n") {
        sendCommand(_commands[INVENTORY]);
    } else {
        sendCommand(_commands[FORWARD]);
    }
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
            stream >> _food;
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

    std::cout << "Food: " << _food << std::endl;

    if (_food < 40) {
        sendCommand(_commands[LOOK]);
    }
}


void Zappy::AI::sendCommand(const std::string &command)
{
    _fd << command;
    _commandQueue.push(command);
    _numberCmd++;
}