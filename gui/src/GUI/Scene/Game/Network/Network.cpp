/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Network
*/

#include "Network.hh"
#include "../Game.hh"

#include <sstream>
#include <utility>
#include <chrono>
#include <thread>

Zappy::Network::Network(std::shared_ptr<CommonElements> commonElements, Game &game):
    _commonElements(commonElements), _game(game)
{
    initCommands();
}

Zappy::Network::~Network()
{
}

void Zappy::Network::checkServer()
{
    std::string temp = GuiSocket::receiveFromServer(_commonElements->getSocket());
    std::stringstream serverInput;
    std::string command;

    while (temp != "") {
        serverInput << temp;
        serverInput >> command;
        if (_commands[command] != nullptr)
            _commands[command](serverInput.str());
        serverInput.str("");
        temp = GuiSocket::receiveFromServer(_commonElements->getSocket());
    }
}

void Zappy::Network::sendQueueToServer()
{
    std::string command;

    while (!_commandsQueue.empty()) {
        command = _commandsQueue.front();
        _commandsQueue.pop();
        GuiSocket::sendToServer(_commonElements->getSocket(), command);
        if (!_commandsQueue.empty())
            std::this_thread::sleep_for(std::chrono::milliseconds(160));
    }
}

void Zappy::Network::addToQueue(const std::string &command)
{
    _commandsQueue.push(command);
}

void Zappy::Network::initCommands()
{
    _commands["msz"] = [this](const std::string &args) { msz(args); };
    _commands["bct"] = [this](const std::string &args) { bct(args); };
    _commands["tna"] = [this](const std::string &args) { tna(args); };
    _commands["pnw"] = [this](const std::string &args) { pnw(args); };
    _commands["ppo"] = [this](const std::string &args) { ppo(args); };
    _commands["plv"] = [this](const std::string &args) { plv(args); };
    _commands["pin"] = [this](const std::string &args) { pin(args); };
    _commands["pex"] = [this](const std::string &args) { pex(args); };
    _commands["pbc"] = [this](const std::string &args) { pbc(args); };
    _commands["pic"] = [this](const std::string &args) { pic(args); };
    _commands["pie"] = [this](const std::string &args) { pie(args); };
    _commands["pfk"] = [this](const std::string &args) { pfk(args); };
    _commands["pdr"] = [this](const std::string &args) { pdr(args); };
    _commands["pgt"] = [this](const std::string &args) { pgt(args); };
    _commands["pdi"] = [this](const std::string &args) { pdi(args); };
    _commands["enw"] = [this](const std::string &args) { enw(args); };
    _commands["ebo"] = [this](const std::string &args) { ebo(args); };
    _commands["edi"] = [this](const std::string &args) { edi(args); };
    _commands["sgt"] = [this](const std::string &args) { sgt(args); };
    _commands["seg"] = [this](const std::string &args) { seg(args); };
    _commands["smg"] = [this](const std::string &args) { smg(args); };
}

void Zappy::Network::msz(const std::string &args)
{
    std::stringstream ss(args);
    std::string temp;
    std::size_t x;
    std::size_t y;

    std::cout << args << std::endl;
    ss >> temp >> x >> y;
    _game.setMapSize(x, y);
}

void Zappy::Network::bct(const std::string &args)
{
    std::stringstream ss(args);
    std::string temp;
    std::size_t x;
    std::size_t y;
    std::vector<std::size_t> resources(7);

    std::cout << args << std::endl;
    ss >> temp >> x >> y >> resources[FOOD] >> resources[LINEMATE] >>
        resources[DERAUMERE] >> resources[SIBUR] >> resources[MENDIANE] >>
        resources[PHIRAS] >> resources[THYSTAME];
    _game.updateTile(x, y, resources);
}

void Zappy::Network::tna(const std::string &args)
{
    std::cout << "tna " << args << std::endl;
}

void Zappy::Network::pnw(const std::string &args)
{
    std::stringstream ss(args);
    std::string temp;
    std::string id;
    std::size_t x;
    std::size_t y;
    std::size_t facingDirection;
    std::size_t level;
    std::string team;

    std::cout << args << std::endl;
    ss >> temp >> id >> x >> y >> facingDirection >> level >> team;
    _game.addPlayer(std::stoi(&id[1]), x, y, static_cast<orientation>(facingDirection),
                    level, team);
}

void Zappy::Network::ppo(const std::string &args)
{
    std::stringstream ss(args);
    std::string temp;
    std::string id;
    std::size_t x;
    std::size_t y;
    std::size_t facingDirection;

    std::cout << args << std::endl;
    ss >> temp >> id >> x >> y >> facingDirection;
    _game.updatePlayerPosition(std::stoi(&id[1]), x, y,
        static_cast<orientation>(facingDirection));
}

void Zappy::Network::plv(const std::string &args)
{
    std::stringstream ss(args);
    std::string temp;
    std::string id;
    std::size_t level;

    std::cout << args << std::endl;
    ss >> temp >> id >> level;
    _game.updatePlayerLevel(std::stoi(&id[1]), level);
}

void Zappy::Network::pin(const std::string &args)
{
    std::stringstream ss(args);
    std::string temp;
    std::string id;
    std::vector<std::size_t> resources(7);

    std::cout << args << std::endl;
    ss >> temp >> id >> resources[FOOD] >> resources[LINEMATE] >>
        resources[DERAUMERE] >> resources[SIBUR] >> resources[MENDIANE] >>
        resources[PHIRAS] >> resources[THYSTAME];
    _game.updatePlayerInventory(std::stoi(&id[1]), resources);
}

void Zappy::Network::pex(const std::string &args)
{
    std::stringstream ss(args);
    std::string temp;
    std::string id;

    std::cout << args << std::endl;
    ss >> temp >> id;
    addToQueue("ppo " + id + "\n");
}

void Zappy::Network::pbc(const std::string &args)
{
    std::cout << "pbc " << args << std::endl;
}

void Zappy::Network::pic(const std::string &args)
{
    std::cout << "pic " << args << std::endl;
}

void Zappy::Network::pie(const std::string &args)
{
    std::cout << "pie " << args << std::endl;
}

void Zappy::Network::pfk(const std::string &args)
{
    std::cout << "pfk " << args << std::endl;
}

void Zappy::Network::pdr(const std::string &args)
{
    // TODO: update player inventory and tile content
    std::cout << "pdr " << args << std::endl;
}

void Zappy::Network::pgt(const std::string &args)
{
    // TODO: update player inventory and tile content
    std::cout << "pgt " << args << std::endl;
}

void Zappy::Network::pdi(const std::string &args)
{
    std::stringstream ss(args);
    std::string temp;
    std::string id;

    std::cout << args << std::endl;
    ss >> temp >> id;
    _game.playerDeath(std::stoi(&id[1]));
}

// TODO: understand how eggs works
void Zappy::Network::enw(const std::string &args)
{
    std::cout << "enw " << args << std::endl;
}

void Zappy::Network::ebo(const std::string &args)
{
    std::cout << "ebo " << args << std::endl;
}

void Zappy::Network::edi(const std::string &args)
{
    std::cout << "edi " << args << std::endl;
}

void Zappy::Network::sgt(const std::string &args)
{
    std::stringstream ss(args);
    std::string temp;
    std::size_t tickTime;

    std::cout << args << std::endl;
    ss >> temp >> tickTime;
    _game.setTickTime(tickTime);
}

void Zappy::Network::sst(const std::string &args)
{
    std::stringstream ss(args);
    std::string temp;
    std::size_t tickTime;

    std::cout << args << std::endl;
    ss >> temp >> tickTime;
    _game.setTickTime(tickTime);
}

void Zappy::Network::seg(const std::string &args)
{
    // TODO: add an end of game boolean
    std::cout << "seg " << args << std::endl;
}

void Zappy::Network::smg(const std::string &args)
{
    std::cout << "smg " << args << std::endl;
}