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
    _commands.push_back("Set ");
    _commands.push_back("Left\n");
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
    _isIncantation = false;
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
    std::string levelUpResponse = "Current level: " + std::to_string(_currentLevel + 1) + "\n";

    _fd >> serverResponse;
    if (serverResponse == levelUpResponse) {
        _isIncantation = false;
        _currentLevel++;
        sendCommand(_commands[LOOK], false);
        return;
    }
    _numberCmd--;
    std::cout << "nbr cmd " << _numberCmd << std::endl;
    if (_numberCmd < 10 && !_commandQueue.empty() && !_isIncantation) {
        command = _commandQueue.front();
        _commandQueue.pop();
        if (Utils::isInventory(serverResponse) && serverResponse != "ok\n" && serverResponse != "ko\n") {
            parseInventory(serverResponse);
        } else if (command == "Look\n" && serverResponse != "ko\n" && serverResponse != "ok\n") {
            handleLook(serverResponse);
        } else if (command == "Take ") {
            handleTakeObjectResponse(serverResponse);
        }
    }
    if (!_isIncantation && _commandQueue.empty()) {
        sendCommand(_commands[LOOK], false);
    }
}

void Zappy::AI::handleLook(const std::string &response)
{
    std::istringstream stream(response.substr(1, response.size() - 3));
    std::string tile = "";
    std::string object = "";
    std::istringstream tileStream;
    bool isObjectTaken = false;
    int tileIndex = 0;

    while (!isObjectTaken && std::getline(stream, tile, ',')) {
        tileStream = std::istringstream(tile);
        if (tileStream >> object && object != "player") {
            handlePlayerMove(tileIndex);
            isObjectTaken = true;
        }
        while (tileStream >> object)
            takeObject(object);
        tileStream.clear();
        tileIndex++;
    }
    sendCommand(_commands[LOOK], false);
}

void Zappy::AI::takeObject(const std::string &object)
{
    if (object != "player" && object != "egg")
        sendCommand(_commands[TAKE_OBJECT], true, object);
}

void Zappy::AI::handlePlayerMove(int tileIndex)
{
    if (tileIndex > 0) {
        if (tileIndex == 1) {
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[RIGHT], false);
        } else if (tileIndex == 2) {
            sendCommand(_commands[FORWARD], false);
        } else if (tileIndex == 3) {
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[RIGHT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
        }
    }
}

void Zappy::AI::handleTakeObjectResponse(const std::string &response)
{
    if (response == "ok\n")
        sendCommand(_commands[INVENTORY], false);
    else
        sendCommand(_commands[FORWARD], false);
}

void Zappy::AI::parseInventory(const std::string &response)
{
    std::istringstream stream(response);
    std::string stringFind;
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
    if (_currentLevel == 1 && linemate >= 1) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[INCANTATION], false);
        _isIncantation = true;
        return;
    }
    if (_food <= 10)
        sendCommand(_commands[LOOK], false);
}


void Zappy::AI::sendCommand(const std::string &command, bool isObject, const std::string &object)
{
    if (_numberCmd > 10)
        return;
    if (isObject) {
        std::cout << "Object take or set -> " << object << std::endl;
        _fd << (command + object + "\n");
        _commandQueue.push(command);
        _numberCmd++;
    }
    if (!isObject) {
        _fd << command;
        _commandQueue.push(command);
        _numberCmd++;
    }
}
