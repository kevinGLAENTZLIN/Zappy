/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Game
*/

#include "Game.hh"
#include "Map/Tiles.hh"
#include "Player/Player.hh"
#include <raylib.h>

Zappy::Game::Game(std::shared_ptr<CommonElements> commonElements):
    _commonElements(commonElements), _timerSizeT(-1), _timer(0), _mapSizeQuery(false),
    _tickTime(-1), _network(commonElements, *this)
{
    loadModels();
    _mapSize = {0, 0};
    _network.addToQueue("msz\n");
    _network.addToQueue("tna\n");
    _network.addToQueue("sgt\n");
    _network.addToQueue("mct\n");
}

Zappy::Game::~Game()
{}

void Zappy::Game::computeLogic()
{
    Raylib::Camera cam = _commonElements->getCamera();
    std::size_t _tickTemp;

    cam.cameraUpdate(CAMERA_ORBITAL);
    _commonElements->setCamera(cam);
    _network.checkServer();
    _network.sendQueueToServer();
    if (_tickTime == -1)
        return;
    _timer += GetFrameTime() / _tickTime;
    _tickTemp = static_cast<std::size_t>(_timer);
    if (_timerSizeT == _tickTemp)
        return;
    _timerSizeT = _tickTemp;
    if (_timerSizeT % 20 == 0)
        _network.addToQueue("mct\n");
    if (_timerSizeT % 126 == 0)
        for (auto &player : _players)
            _network.addToQueue("pin " + std::to_string(player.getId()) + "\n");
}

void Zappy::Game::displayElements(void)
{
    _commonElements->getCamera().begin3DMode();
        if (_tiles.size() != 0)
            for (auto &tile : _tiles)
                tile.Draw();
        for (auto &player : _players)
            player.draw(_mapSize);
    _commonElements->getCamera().end3DMode();
    DrawFPS(0, 0);
}

void Zappy::Game::setMapSize(std::size_t x, std::size_t y)
{
    _mapSize = {static_cast<float>(x), static_cast<float>(y)};
    createMap();
}

void Zappy::Game::setTickTime(std::size_t nbTicksPerSecond)
{
    _tickTime = 1.0 / nbTicksPerSecond;
}

void Zappy::Game::addPlayer(std::size_t id, std::size_t x, std::size_t y,
                           std::size_t playerOrientation, std::size_t level,
                           std::string teamName)
{
    _players.emplace_back(id, x, y, static_cast<orientation>(playerOrientation),
                          level, teamName, _models[PLAYER]);
}

void Zappy::Game::updateTile(std::size_t x, std::size_t y,
                             std::vector<std::size_t> resources)
{
    _tiles[y * _mapSize.x + x].setResources(resources);
}

void Zappy::Game::updatePlayerPosition(std::size_t id, std::size_t x, std::size_t y,
                                      std::size_t playerOrientation)
{
    for (auto &player : _players) {
        if (player.getId() == id)
            return player.setPosition(x, y,
                static_cast<orientation>(playerOrientation));
    }
}

void Zappy::Game::updatePlayerLevel(std::size_t id, std::size_t level)
{
    for (auto &player : _players) {
        if (player.getId() == id) {
            player.setLevel(level);
            return;
        }
    }
}

void Zappy::Game::updatePlayerInventory(std::size_t id, std::vector<std::size_t> resources)
{
    for (auto &player : _players) {
        if (player.getId() == id) {
            player.setInventory(resources);
            return;
        }
    }
}

void Zappy::Game::playerDeath(std::size_t id)
{
    for (std::size_t i = 0; i < _players.size(); i++) {
        if (_players[i].getId() == id) {
            _players.erase(_players.begin() + i);
            return;
        }
    }
}

void Zappy::Game::loadModels()
{
    // FOOD
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/food.obj",
                         "gui/assets/3Delements/food.png", 0, 0, 0, 0, 0, 0, 0.75));
    // LINEMATE
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/redCrystal.obj",
                         "gui/assets/3Delements/redCrystal.png", 0, 0, 0, 0, 0, 0, 0.05));
    // DERAUMERE
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/blueCrystal.obj",
                         "gui/assets/3Delements/blueCrystal.png", 0, 0, 0, 0, 0, 0, 0.05));
    // SIBUR
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/greenCrystal.obj",
                         "gui/assets/3Delements/greenCrystal.png", 0, 0, 0, 0, 0, 0, 0.05));
    // MENDIANE
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/whiteCrystal.obj",
                         "gui/assets/3Delements/whiteCrystal.png", 0, 0, 0, 0, 0, 0, 0.01));
    // PHIRAS
    _models.emplace_back(nullptr);
    // THYSTAME
    _models.emplace_back(nullptr);
    // PLAYER
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/player.obj",
                         "gui/assets/3Delements/food.png", 0, 0, 0, 0, 0, 0, 1));
    // EGG
    _models.emplace_back(nullptr);
}

void Zappy::Game::createMap()
{
    for (int i = 0; i < _mapSize.y; i++)
        for (int j = 0; j < _mapSize.x; j++)
            _tiles.emplace_back(j, i, _mapSize, _models);
}
