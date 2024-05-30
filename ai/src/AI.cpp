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
    if (argc != 7)
        throw Zappy::ErrorAI(ArgError, "invalid number of arguments");
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
    _numberCmd = 0;
    _food = 10;
}

void Zappy::AI::initConnection(void)
{
    int nbInstructions = 0;
    std::string response = "";

    _clientSocket->connectSocket(_port, _ip);
    _fd = _clientSocket->getSocket();
    while (true) {
        if (_clientSocket->selectSocket() == -1) {
            _fd >> response;
            if (nbInstructions == 0 && response == "WELCOME\n")
                _fd << (_teamName + "\n");
            if (nbInstructions == 1)
                _clientNumber = std::stoi(response);
            if (nbInstructions == 2) {
                std::istringstream stream(response);
                stream >> _sizeWorldX >> _sizeWorldY;
            }
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
            sendCommand(_commands[INVENTORY], false);
            firstRun = false;
        }
    }
}

void Zappy::AI::handleResponse(void)
{
    std::string serverResponse = "";
    std::string command = "";

    _fd >> serverResponse;
    std::cout << "nbr cmd: " << _numberCmd << std::endl;
    if (!_commandQueue.empty()) {
        command = _commandQueue.front();
        _commandQueue.pop();
        _numberCmd--;
        if (command == "Inventory\n" && serverResponse != "ko\n" && serverResponse != "ok\n") {
            handleInventoryResponse(serverResponse);
        } else if (command == "Look\n" && serverResponse != "ko\n" && serverResponse != "ok\n") {
            handleLook(serverResponse);
        } else if (command == "Take ") {
            handleTakeObjectResponse(serverResponse);
        } else {
            handleDefaultResponse(serverResponse);
        }
    }
}

void Zappy::AI::handleLook(const std::string &response)
{
    std::istringstream stream(response);
    std::string tile = "";
    std::string object = "";
    std::istringstream tileStream;
    int tileIndex = 0;

    while (std::getline(stream, tile, ',')) {
        tileStream.str(tile);
        while (tileStream >> object) {
            if (object == "food")
                sendCommand(_commands[TAKE_OBJECT], true, object);
            if (object == "linemate")
                sendCommand(_commands[TAKE_OBJECT], true, object);
        }
        tileIndex++;
    }
}

void Zappy::AI::handleInventoryResponse(const std::string &response)
{
    if (Utils::isInventory(response) && response != "ok\n" && response != "ko\n")
        parseInventory(response);
}

void Zappy::AI::handleDefaultResponse(const std::string &response)
{
}

void Zappy::AI::handleTakeObjectResponse(const std::string &response)
{
    std::cout << "Take object response: " << response << std::endl;

    if (response == "ok\n")
        sendCommand(_commands[INVENTORY], false);
    else
        sendCommand(_commands[FORWARD], false);
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
        if (stringFind == "food")
            stream >> _food;
        if (stringFind == "linemate")
            stream >> linemate;
        if (stringFind == "deraumere")
            stream >> deraumere;
        if (stringFind == "sibur")
            stream >> sibur;
        if (stringFind == "mendiane")
            stream >> mendiane;
        if (stringFind == "phiras")
            stream >> phiras;
        if (stringFind == "thystame")
            stream >> thystame;
    }
    if (_food < 40)
        sendCommand(_commands[LOOK], false);
}


void Zappy::AI::sendCommand(const std::string &command, bool isObject, const std::string &object)
{
    if (isObject) {
        std::cout << "Object take -> " << object << std::endl;
        _fd << command + object + "\n";
        _commandQueue.push(command);
        _numberCmd++;
    }
    if (!isObject) {
        _fd << command;
        _commandQueue.push(command);
        _numberCmd++;
    }
}