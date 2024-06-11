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
    _currentLevel = 1;
    _isAlive = true;
    _isBroadcasting = false;
    _moveToBroadcast = false;
    _needToBeFat = false;
    _inventoryReceived = true;
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
    bool firstRun = true;
    while (_isAlive) {
        if (_clientSocket->selectSocket() == -1)
            handleResponse();
        if (_inventoryReceived) {
            sendCommand(_commands[INVENTORY], false);
            _inventoryReceived = false;
        }
    }
}

/* Response global ------------------------------------------------------------------------------------------------------------------------ */

bool Zappy::AI::handleUniqueCommand(const std::string &serverResponse, const std::string &response)
{
    std::string levelUpResponse = "Current level: " + std::to_string(_currentLevel + 1) + "\n";

    if (serverResponse == "dead\n") {
        _isAlive = false;
        _clientSocket->~Socket();
        return true;
    }
    if (serverResponse == levelUpResponse)
        _currentLevel++;
    if (response == "message")
        handleBroadcast(serverResponse);
    return false;
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
    std::cout << "number cmd apres decrementation : " << _numberCmd << std::endl;
    if (!_commandQueue.empty()) {
        _numberCmd--;
        command = _commandQueue.front();
        _commandQueue.pop();
         if (Utils::isInventory(serverResponse) && serverResponse
         != "ok\n" && serverResponse != "ko\n")
            parseInventory(serverResponse);
        else if (command == "Look\n" && serverResponse
        != "ko\n" && serverResponse != "ok\n")
            handleLook(serverResponse);
    } else {
        if (Utils::isInventory(serverResponse) && serverResponse
        != "ok\n" && serverResponse != "ko\n")
            parseInventory(serverResponse);
        else if (command == "Look\n" && serverResponse
        != "ko\n" && serverResponse != "ok\n")
            handleLook(serverResponse);
    }
}

/* Broadcast method ----------------------------------------------------------------------------------------------------------------------- */

void Zappy::AI::moveToBroadcastPosition(int position, int level)
{
    if (_food <= 40)
        return;
    if (level != _currentLevel)
        return;
    _moveToBroadcast = true;
    switch(position) {
        case 0:
            sendCommand(_commands[LOOK], false);
            sendCommand(_commands[INVENTORY], false);
            break;
        case 1:
            sendCommand(_commands[FORWARD], false);
            std::cout << "case 1 dans move broadcast\n";
            break;
        case 2:
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            std::cout << "case 2 dans move broadcast\n";
            break;
        case 3:
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            std::cout << "case 3 dans move broadcast\n";
            break;
        case 4:
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            std::cout << "case 4 dans move broadcast\n";

            break;
        case 5:
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            std::cout << "case 5 dans move broadcast\n";

            break;
        case 6:
            sendCommand(_commands[RIGHT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[RIGHT], false);
            sendCommand(_commands[FORWARD], false);
            std::cout << "case 6 dans move broadcast\n";

            break;
        case 7:
            sendCommand(_commands[RIGHT], false);
            sendCommand(_commands[FORWARD], false);
            std::cout << "case 7 dans move broadcast\n";

            break;
        case 8:
            sendCommand(_commands[RIGHT], false);
            sendCommand(_commands[FORWARD], false);
            sendCommand(_commands[LEFT], false);
            sendCommand(_commands[FORWARD], false);
            std::cout << "case 8 dans move broadcast\n";

            break;
        default:
            std::cerr << "error : " << position << std::endl;
            break;
    }
    _moveToBroadcast = false;
}

void Zappy::AI::handleBroadcast(const std::string &response)
{
    std::istringstream stream(response);
    std::string position;
    int positionInt = 0;
    int level = 0;

    stream >> position;
    stream >> position;
    stream >> level;
    std::cout << "position : " << position << std::endl;
    std::cout << "level : " << level << std::endl;
    positionInt = std::stoi(position);
    moveToBroadcastPosition(positionInt, level);
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
    if (!_isBroadcasting) {
        while (!isObjectTaken && std::getline(stream, tile, ',') && !_moveToBroadcast) {
            tileStream = std::istringstream(tile);
            if (tileStream >> object && object != "player") {
                handlePlayerMove(tileIndex, object);
                isObjectTaken = true;
            }
            while (tileStream >> object) {
                if (object == "player")
                    _nbPlayer++;
                if (object != "player" && object != "egg" && shouldTakeObject(object)) {
                    takeObject(object);
                    isObjectTaken = true;
                }
            }
            tileStream.clear();
            tileIndex++;
        }
    }
    if (_isBroadcasting) {
        while (!isObjectTaken && std::getline(stream, tile, ',')) {
            tileStream = std::istringstream(tile);
            while (tileStream >> object) {
                if (object == "player")
                    _nbPlayer++;
            }
            tileStream.clear();
            tileIndex++;
        }
    }
    std::cout << "\033[1;35m << Is object taken <<\033[0m\n" << isObjectTaken;
    if (!isObjectTaken && !_isBroadcasting)
        playerLife();
}

void Zappy::AI::playerLife(void)
{
    static int moveCounter = 0;

    switch (moveCounter % 4) {
        case 0:
            sendCommand(_commands[FORWARD], false);
            break;
        case 1:
            sendCommand(_commands[RIGHT], false);
            break;
        case 2:
            sendCommand(_commands[FORWARD], false);
            break;
        case 3:
            sendCommand(_commands[LEFT], false);
            break;
    }
    moveCounter++;
}

bool Zappy::AI::shouldTakeObject(const std::string &object)
{
    if (object == "food" && _needToBeFat)
        return true;
    if (_food > MAX_FOOD && object == "food")
        return false;
    if (_food > MIN_FOOD && _currentLevel == 1 && (object == "linemate" || object == "thystame"))
        return true;
    if (_food > MIN_FOOD && _currentLevel == 2 && (object == "linemate" || object == "deraumere"
    || object == "sibur" || object == "thystame"))
        return true;
    if (_food > MIN_FOOD && _currentLevel == 3 && (object == "linemate" || object == "phiras"
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

    if (tileIndex > 0 && !_isBroadcasting) {
        std::cout << "tile index : " << tileIndex << std::endl;
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

/* Object handling ----------------------------------------------------------------------------------------------------------------------- */

void Zappy::AI::takeObject(const std::string &object)
{
    if (object != "player" && object != "egg")
        sendCommand(_commands[TAKE_OBJECT], true, object);
}

// void Zappy::AI::handleTakeObjectResponse(const std::string &response)
// {
//     if (response == "ok\n")
//         sendCommand(_commands[INVENTORY], false);
// }

/* Incantation method --------------------------------------------------------------------------------------------------------------------- */

bool Zappy::AI::handleIncantation(int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
    if (_food <= 50)
        return false;
    if (_currentLevel == 1 && linemate >= 1) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[INCANTATION], false);
        return true;
    }
    std::cout << "\033[44m nb player -> " << _nbPlayer << "\033[0m\n";
    if (_currentLevel == 2 && linemate >= 1 && deraumere >= 1 && sibur >= 1 && _nbPlayer == 2) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "deraumere");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[INCANTATION], false);
        _canBroadcast = false;
        _isBroadcasting = false;
        return true;
    }
    if (_currentLevel == 3 && linemate >= 2 && phiras >= 1 && sibur >= 1 && _nbPlayer == 2) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "phiras");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[INCANTATION], false);
        _canBroadcast = false;
        _isBroadcasting = false;
        return true;
    }
    if (_currentLevel == 4 && linemate >= 1 && deraumere >= 1 && sibur >= 2 && phiras >= 1 && _nbPlayer == 4) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "deraumere");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[SET_OBJECT], true, "phiras");
        sendCommand(_commands[INCANTATION], false);
        _canBroadcast = false;
        _isBroadcasting = false;
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
        _canBroadcast = false;
        _isBroadcasting = false;
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
        _canBroadcast = false;
        _isBroadcasting = false;
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
        _canBroadcast = false;
        _isBroadcasting = false;
        return true;
    }
    return false;
}

bool Zappy::AI::canIncantation(int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
    if (_food <= 50)
        return false;
    if (_currentLevel == 1 && linemate >= 1)
        return true;
    if (_currentLevel == 2 && linemate >= 1 && deraumere >= 1 && sibur >= 1)
        return true;
    if (_currentLevel == 3 && linemate >= 2 && phiras >= 1 && sibur >= 1)
        return true;
    if (_currentLevel == 4 && linemate >= 1 && deraumere >= 1 && sibur >= 2 && phiras >= 1)
        return true;
    if (_currentLevel == 5 && linemate >= 1 && deraumere >= 2 && sibur >= 1 && mendiane >= 3)
        return true;
    if (_currentLevel == 6 && linemate >= 1 && deraumere >= 2 && sibur >= 3 && phiras >= 1)
        return true;
    if (_currentLevel == 7 && linemate >= 2 && deraumere >= 2 && sibur >= 2 && mendiane >= 2 && phiras >= 2 && thystame >= 1)
        return true;
    return false;
}

/* Phase method ----------------------------------------------------------------------------------------------------------------------- */

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
    _inventoryReceived = true;
    handleIncantation(linemate, deraumere, sibur, mendiane, phiras, thystame);
    setPhase(canIncantation(linemate, deraumere, sibur, mendiane, phiras, thystame));
    handlePhase(canIncantation(linemate, deraumere, sibur, mendiane, phiras, thystame));
}

void Zappy::AI::setPhase(bool canIncantation)
{
    if ((canIncantation && _food < INCANTATION_FOOD && !_canBroadcast)
    || (_food < MIN_FOOD && _canBroadcast)) {
        _canBroadcast = false;
        _isBroadcasting = false;
        _needToBeFat = true;
        phaseFood();
    }
    if (canIncantation && _food >= INCANTATION_FOOD
    && !_canBroadcast && _currentLevel >= 2 && _currentLevel < 8)
        _canBroadcast = true;
    if (_food > INCANTATION_FOOD && _currentLevel >= 2 && _currentLevel <= 7)
        _isBroadcasting = true;
    if (_food < INCANTATION_FOOD && _isBroadcasting) {
        _needToBeFat = true;
        _isBroadcasting = false;
    }
    if (_food < MIN_FOOD || _currentLevel == 8) {
        _needToBeFat = true;
    }
    if (_food >= MAX_FOOD) {
        _needToBeFat = false;
        std::cout << "\033[1;34m" << "Food phase OVER" << "\033[0m\n" << std::endl;     // Blue
    }
}

void Zappy::AI::handlePhase(bool canIncantation)
{
    if (_isBroadcasting) {
        std::cout << "\033[1;33m" << "Broadcasting phase" << "\033[0m\n" << std::endl;  // Yellow
        phaseBroadcast();
    }
    if (_food > MIN_FOOD && !_needToBeFat && !_isBroadcasting) {
        std::cout << "\033[1;35m" << "Stone phase" << "\033[0m\n" << std::endl;         // Magenta
        phaseStone();
    }
    if (!canIncantation) {
        std::cout << "\033[1;32m" << "Can't Incant" << "\033[0m\n" << std::endl;        // Green
        _needToBeFat = true;
    }
    if (_needToBeFat && !_isBroadcasting) {
        std::cout << "\033[1;31m" << "Food phase" << "\033[0m\n" << std::endl;          // Red
        phaseFood();
    }
    if (_canBroadcast)
        phaseBroadcast();
}

void Zappy::AI::phaseFood(void)
{
    sendCommand(_commands[LOOK], false);
}

void Zappy::AI::phaseStone(void)
{
    sendCommand(_commands[LOOK], false);
}

void Zappy::AI::phaseBroadcast(void)
{
    sendCommand(_commands[BROADCAST], true, std::to_string(_currentLevel));
    sendCommand(_commands[LOOK], false);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

/* Send command --------------------------------------------------------------------------------------------------------------------------- */

void Zappy::AI::sendCommand(const std::string &command, bool isObject, const std::string &object)
{
    if (_numberCmd > 9)
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
    std::cout << "number cmd apres ajout : " << _numberCmd << std::endl;
}
