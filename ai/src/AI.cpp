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
    _commands.push_back("Broadcast ");
    _commands.push_back("Connect_nbr\n");
    _commands.push_back("Eject\n");
    _commands.push_back("Take ");
    _commands.push_back("Set ");
    _commands.push_back("Left\n");
}

/* Check arg method ----------------------------------------------------------------------------------------------------------------------- */

void Zappy::AI::checkArg(int argc, char **argv)
{
    if (argc != 7)
        throw Zappy::ErrorAI(ArgError, "invalid number of arguments");
    if (std::string(argv[1]) != "-p" || std::string(argv[3]) != "-n" ||
        std::string(argv[5]) != "-h") {
        throw Zappy::ErrorAI(ArgError, "-p or -n or -h missing, check -h");
    }
}

/* Init method ---------------------------------------------------------------------------------------------------------------------------- */

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

/* Run method ----------------------------------------------------------------------------------------------------------------------------- */

void Zappy::AI::run(void)
{
    while (_isAlive) {
        if (_clientSocket->selectSocket() == -1)
            handleResponse();
    }
}

/* Response global ------------------------------------------------------------------------------------------------------------------------ */

void Zappy::AI::handleUniqueCommand(const std::string &serverResponse, const std::string &response)
{
    std::string levelUpResponse = "Current level: " + std::to_string(_currentLevel + 1) + "\n";

    if (serverResponse == "dead\n") {
        _isAlive = false;
        _clientSocket->~Socket();    
    }
    if (serverResponse == levelUpResponse)
        _currentLevel++;
    if (response == "message")
        handleBroadcast(serverResponse);
}

void Zappy::AI::handleResponse(void)
{
    std::string serverResponse = "";
    std::string response = "";
    std::string command = "";
    std::istringstream stream;

    _fd >> serverResponse;
    stream = std::istringstream(serverResponse);
    stream >> response;
    handleUniqueCommand(serverResponse, response);
    _numberCmd--;
    if (_numberCmd < 10 && !_commandQueue.empty()) {
        command = _commandQueue.front();
        _commandQueue.pop();
    }
}

/* Broadcast method ----------------------------------------------------------------------------------------------------------------------- */

void Zappy::AI::moveToBroadcastPosition(int position)
{
    switch(position) {
        case 0:
            sendCommand(_commands[LOOK], false);
            sendCommand(_commands[INVENTORY], false);
            break;
        case 1:
            sendCommand(_commands[FORWARD], false);
            break;
        case 2:
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            break;
        case 3:
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            break;
        case 4:
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            break;
        case 5:
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            break;
        case 6:
            sendCommand(_commands[RIGHT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[RIGHT], false);
            sendCommand(_commands[FORWARD], false);
            break;
        case 7:
            sendCommand(_commands[RIGHT], false);
            sendCommand(_commands[FORWARD], false);
            break;
        case 8:
            sendCommand(_commands[RIGHT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            break;
        default:
            std::cerr << "error : " << position << std::endl;
            break;
    }
}

void Zappy::AI::handleBroadcast(const std::string &response)
{
    std::istringstream stream(response);
    std::string position;
    int positionInt = 0;

    stream >> position;
    stream >> position;
    positionInt = std::stoi(position);
    moveToBroadcastPosition(positionInt);
}

/* Look method ---------------------------------------------------------------------------------------------------------------------------- */

void Zappy::AI::handleLook(const std::string &response)
{
    std::istringstream stream(response.substr(1, response.size() - 3));
    std::string tile = "";
    std::string object = "";
    std::istringstream tileStream;
    bool isObjectTaken = false;
    int tileIndex = 0;

    _nbPlayer = 0;
    while (!isObjectTaken && std::getline(stream, tile, ',')) {
        tileStream = std::istringstream(tile);
        if (tileStream >> object && object != "player") {
            handlePlayerMove(tileIndex, object);
            isObjectTaken = true;
        }
        while (tileStream >> object) {
            if (object != "player" && object != "egg" && shouldTakeObject(object)) {
                takeObject(object);
                isObjectTaken = true;
            }
        }
        tileStream.clear();
        tileIndex++;
    }
}

bool Zappy::AI::shouldTakeObject(const std::string &object)
{
    if (_currentLevel == 1 && (object == "food" || object == "linemate" || object == "thystame"))
        return true;
    if (_currentLevel == 2 && (object == "food" || object == "linemate" || object == "deraumere"
    || object == "sibur" || object == "thystame"))
        return true;
    if (_currentLevel == 3 && (object == "food" || object == "linemate" || object == "phiras"
    || object == "sibur" || object == "thystame"))
        return true;
    if (_currentLevel == 4 && (object == "food" || object == "linemate" || object == "deraumere"
    || object == "sibur" || object == "phiras" || object == "thystame"))
        return true;
    if (_currentLevel == 5 && (object == "food" || object == "linemate" || object == "deraumere"
    || object == "sibur" || object == "mendiane" || object == "thystame"))
        return true;
    if (_currentLevel == 6 && (object == "food" || object == "linemate" || object == "deraumere"
    || object == "sibur" || object == "phiras" || object == "thystame"))
        return true;
    if (_currentLevel == 7 && (object == "food" || object == "linemate" || object == "deraumere" || object == "sibur"
    || object == "mendiane" || object == "phiras" || object == "thystame"))
        return true;
    return false;
}

void Zappy::AI::handlePlayerMove(int tileIndex, std::string object)
{
    bool isObjectInterresting = false;

    if (tileIndex > 0) {
        if (tileIndex == 1) {
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[RIGHT], false);
            isObjectInterresting = true;
        }
        if (tileIndex == 2) {
            sendCommand(_commands[FORWARD], false);
            isObjectInterresting = true;
        }
        if (tileIndex == 3) {
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[RIGHT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            isObjectInterresting = true;
        }
        if (tileIndex == 4) {
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[RIGHT], false);
            isObjectInterresting = true;
        }
        if (tileIndex == 5) {
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[RIGHT], false);
            isObjectInterresting = true;
        }
        if (tileIndex == 6) {
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[FORWARD], false);
            isObjectInterresting = true;
        }
        if (tileIndex == 7) {
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[RIGHT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            isObjectInterresting = true;
        }
        if (tileIndex == 8) {
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[RIGHT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            isObjectInterresting = true;
        }
    }
    if (!isObjectInterresting)
        sendCommand(_commands[FORWARD], false);
}

/* Object handeling ----------------------------------------------------------------------------------------------------------------------- */

void Zappy::AI::takeObject(const std::string &object)
{
    if (object != "player" && object != "egg")
        sendCommand(_commands[TAKE_OBJECT], true, object);
}

void Zappy::AI::handleTakeObjectResponse(const std::string &response)
{
    if (response == "ok\n")
        sendCommand(_commands[INVENTORY], false);
}

/* Incantation method --------------------------------------------------------------------------------------------------------------------- */

bool Zappy::AI::handleIncantation(int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
    if (_currentLevel == 1 && linemate >= 1) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[INCANTATION], false);
        return true;
    }
    if (_currentLevel == 2 && linemate >= 1 && deraumere >= 1 && sibur >= 1 && _nbPlayer == 2) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "deraumere");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[INCANTATION], false);
        return true;
    }
    if (_currentLevel == 3 && linemate >= 2 && phiras >= 1 && sibur >= 1 && _nbPlayer == 2) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "phiras");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[INCANTATION], false);
        return true;
    }
    if (_currentLevel == 4 && linemate >= 1 && deraumere >= 1 && sibur >= 2 && phiras >= 1 && _nbPlayer == 4) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "deraumere");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[SET_OBJECT], true, "phiras");
        sendCommand(_commands[INCANTATION], false);
        return true;
    }
    if (_currentLevel == 5 && linemate >= 1 && deraumere >= 2 && sibur >= 1 && mendiane >= 3 && _nbPlayer == 4) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "deraumere");
        sendCommand(_commands[SET_OBJECT], true, "deraumere");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[SET_OBJECT], true, "mendiane");
        sendCommand(_commands[SET_OBJECT], true, "mendiane");
        sendCommand(_commands[SET_OBJECT], true, "mendiane");
        sendCommand(_commands[INCANTATION], false);
        return true;
    }
    if (_currentLevel == 6 && linemate >= 1 && deraumere >= 2 && sibur >= 3 && phiras >= 1 && _nbPlayer == 6) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "deraumere");
        sendCommand(_commands[SET_OBJECT], true, "deraumere");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[SET_OBJECT], true, "phiras");
        sendCommand(_commands[INCANTATION], false);
        return true;
    }
    if (_currentLevel == 7 && linemate >= 2 && deraumere >= 2 && sibur >= 2 && mendiane >= 2 && phiras >= 2 && thystame >= 1 && _nbPlayer == 6) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "deraumere");
        sendCommand(_commands[SET_OBJECT], true, "deraumere");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[SET_OBJECT], true, "mendiane");
        sendCommand(_commands[SET_OBJECT], true, "mendiane");
        sendCommand(_commands[SET_OBJECT], true, "phiras");
        sendCommand(_commands[SET_OBJECT], true, "phiras");
        sendCommand(_commands[SET_OBJECT], true, "thystame");
        sendCommand(_commands[INCANTATION], false);
        return true;
    }
    return false;
}

/* Inventory method ----------------------------------------------------------------------------------------------------------------------- */

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
}

/* Send command --------------------------------------------------------------------------------------------------------------------------- */

void Zappy::AI::sendCommand(const std::string &command, bool isObject, const std::string &object)
{
    if (_numberCmd > 10)
        return;
    if (isObject) {
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
