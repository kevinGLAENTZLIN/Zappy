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
    _firstRun = true;
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

    while (nbInstructions < 3) {
        if (_clientSocket->selectSocket() == -1) {
            _fd >> response;
            if (nbInstructions == 0 && response == "WELCOME\n") {
                _fd << (_teamName + "\n");
                nbInstructions++;
            }
            else if (nbInstructions == 1) {
                _clientNumber = std::stoi(response);
                nbInstructions++;
            }
            else if (nbInstructions == 2) {
                std::istringstream stream(response);
                stream >> _sizeWorldX >> _sizeWorldY;
                nbInstructions++;
            }
        }
    }
}

/* Run method ----------------------------------------------------------------------------------------------------------------------------- */

void Zappy::AI::run(void)
{
    _lastResponseTime = std::chrono::steady_clock::now();
    while (_isAlive) {
        if (_clientSocket->selectSocket() == -1)
            handleResponse();
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - _lastResponseTime).count() >= 2) {
            sendCommand(_commands[INVENTORY], false);
            _lastResponseTime = now;
        }
        if (_inventoryReceived && !_moveToBroadcast) {
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
    if (serverResponse == levelUpResponse) {
        _currentLevel++;
        _moveToBroadcast = false;
        _canBroadcast = false;
        _isBroadcasting = false;
        _inventoryReceived = true;
        _needToBeFat = false;
        return true;
    }
    if (response == "message" && _food > 25) {
        handleBroadcast(serverResponse);
        return true;
    }
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
    if (response != "message")
        _lastResponseTime = std::chrono::steady_clock::now();
    if (handleUniqueCommand(serverResponse, response))
        return;
    if (!_commandQueue.empty()) {
        _numberCmd--;
        command = _commandQueue.front();
        _commandQueue.pop();
    }
    if (Utils::isInventory(serverResponse) && serverResponse != "ok\n" && serverResponse != "ko\n")
        parseInventory(serverResponse);
    else if (command == "Look\n" && serverResponse != "ko\n" && serverResponse != "ok\n")
        handleLook(serverResponse);
}

/* Broadcast method ----------------------------------------------------------------------------------------------------------------------- */

void Zappy::AI::moveToBroadcastPosition(int position, int level)
{
    if (_food < 25) {
        _needToBeFat = true;
        return;
    }
    if (level != _currentLevel) {
        return;
    }
    _moveToBroadcast = true;
    _needToBeFat = false;
    switch(position) {
        case 0:
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
    std::string level;
    int positionInt = 0;
    int levelInt = 0;

    stream >> position;
    stream >> position;
    stream >> level;
    positionInt = std::stoi(position);
    levelInt = std::stoi(level);
    moveToBroadcastPosition(positionInt, levelInt);
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
    if (!_isBroadcasting && !_moveToBroadcast) {
        while (!isObjectTaken && std::getline(stream, tile, ',')) {
            tileStream = std::istringstream(tile);
            if (tileStream >> object && object != "player") {
                handlePlayerMove(tileIndex);
                isObjectTaken = true;
            }
            while (tileStream >> object) {
                if (object != "player" && object != "egg"&& shouldTakeObject(object)) {
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
    if (!isObjectTaken && !_isBroadcasting && !_moveToBroadcast)
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
    int linemateQtt[7] =  {9,8,7,5,4,3,2};
    int deraumereQtt[7] = {8,8,7,7,6,4,2};
    int siburQtt[7] =     {10,10,9,8,6,5,2};
    int mendianeQtt[7] =  {5,5,5,5,5,2,2};
    int phirasQtt[7] =    {6,6,6,4,3,3,2};
    int thystameQtt[7] =  {1,1,1,1,1,1,1};

    if (object == "food" && _needToBeFat)
        return true;
    if (_food > MAX_FOOD && object == "food")
        return false;
    if ((object == "linemate" && _linemate >= linemateQtt[_currentLevel - 1]) ||
        (object == "deraumere" && _deraumere >= deraumereQtt[_currentLevel - 1]) ||
        (object == "sibur" && _sibur >= siburQtt[_currentLevel - 1]) ||
        (object == "mendiane" && _mendiane >= mendianeQtt[_currentLevel - 1]) ||
        (object == "phiras" && _phiras >= phirasQtt[_currentLevel - 1]) ||
        (object == "thystame" && _thystame >= thystameQtt[_currentLevel - 1])
    )
        return false;
    if (_food > MIN_FOOD && _currentLevel == 1 && (object == "linemate" || object == "thystame"))
        return true;
    if (_food > MIN_FOOD && _currentLevel == 2 && (object == "linemate" || object == "deraumere"
    || object == "sibur" || object == "thystame"))
        return true;
    if (_food > MIN_FOOD && _currentLevel == 3 && (object == "linemate" || object == "phiras"
    || object == "sibur" || object == "thystame"))
        return true;
    if (_food > MIN_FOOD && _currentLevel == 4 && (object == "linemate" || object == "deraumere"
    || object == "sibur" || object == "phiras" || object == "thystame"))
        return true;
    if (_food > MIN_FOOD && _currentLevel == 5 && (object == "linemate" || object == "deraumere"
    || object == "sibur" || object == "mendiane" || object == "thystame"))
        return true;
    if (_food > MIN_FOOD && _currentLevel == 6 && (object == "linemate" || object == "deraumere"
    || object == "sibur" || object == "phiras" || object == "thystame"))
        return true;
    if (_food > MIN_FOOD && _currentLevel == 7 && (object == "linemate" || object == "deraumere" || object == "sibur"
    || object == "mendiane" || object == "phiras" || object == "thystame"))
        return true;
    return false;
}

void Zappy::AI::handlePlayerMove(int tileIndex)
{
    bool isObjectInterresting = false;

    if (tileIndex > 0 && !_isBroadcasting) {
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

/* Incantation method --------------------------------------------------------------------------------------------------------------------- */

bool Zappy::AI::handleIncantation(int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
    if (_food <= 40)
        return false;
    if (_currentLevel == 1 && linemate >= 1) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[INCANTATION], false);
        return true;
    }
    if (_currentLevel == 2 && linemate >= 1 && deraumere >= 1 && sibur >= 1 && _nbPlayer >= 2) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "deraumere");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[INCANTATION], false);
        return true;
    }
    if (_currentLevel == 3 && linemate >= 2 && phiras >= 1 && sibur >= 1 && _nbPlayer >= 2) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "phiras");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[INCANTATION], false);
        return true;
    }
    if (_currentLevel == 4 && linemate >= 1 && deraumere >= 1 && sibur >= 2 && phiras >= 1 && _nbPlayer >= 4) {
        sendCommand(_commands[SET_OBJECT], true, "linemate");
        sendCommand(_commands[SET_OBJECT], true, "deraumere");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[SET_OBJECT], true, "sibur");
        sendCommand(_commands[SET_OBJECT], true, "phiras");
        sendCommand(_commands[INCANTATION], false);
        return true;
    }
    if (_currentLevel == 5 && linemate >= 1 && deraumere >= 2 && sibur >= 1 && mendiane >= 3 && _nbPlayer >= 4) {
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
    if (_currentLevel == 6 && linemate >= 1 && deraumere >= 2 && sibur >= 3 && phiras >= 1 && _nbPlayer >= 6) {
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
    if (_currentLevel == 7 && linemate >= 2 && deraumere >= 2 && sibur >= 2 && mendiane >= 2 && phiras >= 2 && thystame >= 1 && _nbPlayer >= 6) {
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

bool Zappy::AI::canIncantation(int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
    if (_food <= 40)
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

    while (stream >> stringFind) {
        if (stringFind == "food")
            stream >> _food;
        if (stringFind == "linemate")
            stream >> _linemate;
        if (stringFind == "deraumere")
            stream >> _deraumere;
        if (stringFind == "sibur")
            stream >> _sibur;
        if (stringFind == "mendiane")
            stream >> _mendiane;
        if (stringFind == "phiras")
            stream >> _phiras;
        if (stringFind == "thystame")
            stream >> _thystame;
    }
    if (_firstRun) {
        sendCommand(_commands[FORK], false);
        _firstRun = false;
    }
    _inventoryReceived = true;
    handleIncantation(_linemate, _deraumere, _sibur, _mendiane, _phiras, _thystame);
    setPhase(canIncantation(_linemate, _deraumere, _sibur, _mendiane, _phiras, _thystame));
    handlePhase(canIncantation(_linemate, _deraumere, _sibur, _mendiane, _phiras, _thystame));
}

void Zappy::AI::setPhase(bool canIncantation)
{
    if (_moveToBroadcast && _food < 25) {
        _moveToBroadcast = false;
        _needToBeFat = true;
        phaseFood();
    }
    if (_moveToBroadcast)
        return;
    if ((canIncantation && _food < MIN_FOOD && !_canBroadcast && !_moveToBroadcast)
    || (_food < MIN_FOOD && _canBroadcast && !_moveToBroadcast)) {
        _canBroadcast = false;
        _isBroadcasting = false;
        _needToBeFat = true;
        phaseFood();
    }
    if (canIncantation && _food >= INCANTATION_FOOD
    && !_canBroadcast && _currentLevel >= 2 && _currentLevel < 8) {
        _canBroadcast = true;
    }
    if (_food > INCANTATION_FOOD && _currentLevel >= 2 && _currentLevel <= 7) {
        _isBroadcasting = true;
    }
    if (_food < MIN_FOOD || _currentLevel == 8) {
        _needToBeFat = true;
    }
    if (_food >= MAX_FOOD) {
        _needToBeFat = false;
    }
}

void Zappy::AI::handlePhase(bool canIncantation)
{
    if (_isBroadcasting) {
        phaseBroadcast();
    }
    if (_food > MIN_FOOD && !_needToBeFat && !_isBroadcasting) {
        phaseStone();
    }
    if (!canIncantation) {
        _needToBeFat = true;
    }
    if (_needToBeFat && !_isBroadcasting) {
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
    _isBroadcasting = true;
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
}
