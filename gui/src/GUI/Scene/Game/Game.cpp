/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Game
*/

#include "Game.hh"
#include "Elements.hh"
#include "Map/Tiles.hh"
#include "Player/Player.hh"
#include <raylib.h>
#include <thread>

Zappy::Game::Game(std::shared_ptr<CommonElements> commonElements):
    _commonElements(commonElements), _timerSizeT(-1), _timer(0), _mapSizeQuery(false),
    _tickTime(-1), _network(commonElements, *this), _pauseMenu(_commonElements),
    _skybox("gui/assets/Skybox/skybox.png", "gui/assets/Skybox/skybox.vs", "gui/assets/Skybox/skybox.fs",
        "gui/assets/Skybox/cubemap.vs", "gui/assets/Skybox/cubemap.fs")
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

    if (_pauseMenu.isVisible() == true)
        return _pauseMenu.computeLogic(_mapSize);
    _network.sendQueueToServer();
    _network.checkServer();
    if (_popUp.getStatus() == true) {
        if (_selectedObjectType == PLAYERTYPE) {
            _popUp.setInfo(_players[_selectedObject]);
            cam.setCameraTarget(_players[_selectedObject].get3DPosition());
        }
        if (_selectedObjectType == TILETYPE) {
            _popUp.setInfo(_tiles[_selectedObject], findPlayersFromCoordinates(_tiles[_selectedObject].getIndex()),
                           findEggsFromCoordinates(_tiles[_selectedObject].getIndex()));
        }
    } else {
        cam.cameraUpdate(CAMERA_FREE);
    }
    userInteractions(cam);
    _commonElements->setCamera(cam);
    if (_tickTime == -1)
        return;
    _timer += GetFrameTime() / _tickTime;
    _tickTemp = static_cast<std::size_t>(_timer);
    if (_timerSizeT == _tickTemp)
        return;
    _timerSizeT = _tickTemp;
    if (_timerSizeT % 40 == 0)
        GuiSocket::sendToServer(_commonElements->getSocket(), "mct\n");
    if (_timerSizeT % 126 == 0) {
        for (auto &player : _players)
            GuiSocket::sendToServer(_commonElements->getSocket(), "pin #" +
                                    std::to_string(player.getId()) + "\n");
    }
}

void Zappy::Game::displayElements(void)
{
    _commonElements->getCamera().begin3DMode();
        _skybox.Draw();
        _commonElements->getMap()->ModelDraw();
        if (_tiles.size() != 0)
            for (auto &tile : _tiles)
                tile.Draw();
        for (auto &player : _players)
            player.draw();
        for (auto &egg : _eggs)
            egg.Draw(_mapSize);
    _commonElements->getCamera().end3DMode();
    _gameInfo.display();
    if (_popUp.getStatus() == true && _pauseMenu.isVisible() == false)
        _popUp.Draw();
    if (_pauseMenu.isVisible() == true)
        _pauseMenu.Draw();
}

void Zappy::Game::setMapSize(std::size_t x, std::size_t y)
{
    _mapSize = {static_cast<float>(x), static_cast<float>(y)};
    if (y > x) {
        _commonElements->getCamera().setCameraDistanceToFocusHard(y);
        _commonElements->getMap()->setScale((y * SCALE_42) / 42.0f);
    } else {
        _commonElements->getCamera().setCameraDistanceToFocusHard(x);
        _commonElements->getMap()->setScale((x * SCALE_42) / 42.0f);
    }
    createMap();
}

void Zappy::Game::setTickTime(std::size_t nbTicksPerSecond)
{
    _tickTime = 1.0 / nbTicksPerSecond;
}

Vector2 Zappy::Game::getPlayerPosition(std::size_t id)
{
    for (auto &player : _players) {
        if (player.getId() == id)
            return player.getPosition();
    }
    return {-1, -1};
}

void Zappy::Game::addPlayer(std::size_t id, std::size_t x, std::size_t y,
                           std::size_t playerOrientation, std::size_t level,
                           std::string teamName)
{
    _players.emplace_back(id, x, y, playerOrientation, level, teamName,
                          _models[PLAYER]);
    _gameInfo.updateTitle(_players.size());
    _gameInfo.updateValues(findAllLevels());
}

void Zappy::Game::updateStatus(std::size_t id, playerStatus status)
{
    for (auto &player : _players) {
        if (player.getId() == id) {
            player.setStatus(status);
            return;
        }
    }
}

void Zappy::Game::updateStatus(std::size_t x, std::size_t y, playerStatus status)
{
    for (auto &player : _players) {
        _network.addToQueue("plv #" + std::to_string(player.getId()) + "\n");
        if (player.getPosition().x == x && player.getPosition().y == y)
            player.setStatus(status);
    }
}

void Zappy::Game::updateTile(std::size_t x, std::size_t y,
                             std::vector<std::size_t> resources)
{
    _tiles[y * _mapSize.x + x].setResources(resources);
}

void Zappy::Game::addEgg(std::size_t id, std::size_t x, std::size_t y)
{
    _eggs.emplace_back(id, x, y, _models[EGG]);
}

void Zappy::Game::addEgg(std::size_t id, std::size_t playerID)
{
    for (auto &player : _players) {
        if (player.getId() == playerID) {
            _eggs.emplace_back(id, player.getPosition().x, player.getPosition().y,
                               _models[EGG]);
            return;
        }
    }
}

void Zappy::Game::removeEgg(std::size_t id)
{
    for (std::size_t i = 0; i < _eggs.size(); i++) {
        if (_eggs[i].getId() == id) {
            _eggs.erase(_eggs.begin() + i);
            return;
        }
    }
}

void Zappy::Game::updatePlayerPosition(std::size_t id, std::size_t x, std::size_t y,
                                      std::size_t playerOrientation)
{
    for (auto &player : _players) {
        if (player.getId() == id)
            return player.setPosition(x, y,
                playerOrientation, _mapSize);
    }
}

void Zappy::Game::updatePlayerLevel(std::size_t id, std::size_t level)
{
    std::string teamName = "";

    for (auto &player : _players) {
        if (player.getId() == id && player.getLevel() != level) {
            player.setLevel(level);
            teamName = player.getTeam();
            break;
        }
    }
    if (teamName == "")
        return;
    _gameInfo.updateValues(findAllLevels());
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
            if (_selectedObject == i && _selectedObjectType == PLAYERTYPE)
                _popUp.setStatus(false);
            _players.erase(_players.begin() + i);
            _gameInfo.updateTitle(_players.size());
            _gameInfo.updateValues(findAllLevels());
            return;
        }
    }
}

void Zappy::Game::playerBroadcast(std::size_t id, const std::string &message)
{
    for (auto &player : _players) {
        if (player.getId() == id) {
            player.broadcast(message);
            return;
        }
    }
}

std::size_t Zappy::Game::findPlayersFromCoordinates(Vector2 coordinates)
{
    std::size_t playersOnTile = 0;

    for (auto &player : _players) {
        if (player.getPosition().x == coordinates.x &&
            player.getPosition().y == coordinates.y)
            playersOnTile++;
    }
    return playersOnTile;
}

std::size_t Zappy::Game::findEggsFromCoordinates(Vector2 coordinates)
{
    std::size_t eggsOnTile = 0;

    for (auto &egg : _eggs) {
        if (egg.getPosition().x == coordinates.x &&
            egg.getPosition().y == coordinates.y)
            eggsOnTile++;
    }
    return eggsOnTile;
}

void Zappy::Game::userInteractions(Raylib::Camera &cam)
{
    Ray ray;
    float mouseWheel = GetMouseWheelMove();

    if (mouseWheel != 0 && _popUp.getStatus() == true)
        cam.setCameraDistanceToFocus(mouseWheel);
    if (IsKeyPressed(KEY_ESCAPE))
        return _pauseMenu.changeVisibility();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (_popUp.getStatus() == true && _popUp.Hits(GetMousePosition()) == true)
            return;
        if (_popUp.getStatus() == true && _popUp.Hits(GetMousePosition()) == false) {
            _popUp.setStatus(false);
            return;
        }
        ray = GetMouseRay(GetMousePosition(), _commonElements->getCamera().getCamera());
        for (std::size_t i = 0; i < _players.size(); i++) {
            if (_players[i].hit(ray) == true) {
                _selectedObject = i;
                _selectedObjectType = PLAYERTYPE;
                _popUp.setStatus(true);
                return;
            }
        }
        for (std::size_t i = 0; i < _mapSize.x * _mapSize.y; i++)
            if (_tiles[i].Hits(ray)) {
                _selectedObject = i;
                _selectedObjectType = TILETYPE;
                _popUp.setStatus(true);
                cam.setCameraTarget({static_cast<float>(_tiles[i].getIndex().x -
                                    _mapSize.x / 2 + 0.5), 0,
                                    static_cast<float>(_tiles[i].getIndex().y -
                                    _mapSize.y / 2 + 0.5)});
                return;
            }
    }
}

std::vector<std::size_t> Zappy::Game::findAllLevels()
{
    std::vector<std::size_t> levels(8, 0);

    for (auto &player : _players)
        levels[player.getLevel() - 1]++;
    return levels;
}

void Zappy::Game::loadModels()
{
    // FOOD
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/food.obj",
                         "gui/assets/3Delements/food.png", 0, 0, 0, 0, 0.75));
    // LINEMATE
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/redCrystal.obj",
                         "gui/assets/3Delements/redCrystal.png", 0, 0, 0, 0, 0.05));
    // DERAUMERE
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/blueCrystal.obj",
                         "gui/assets/3Delements/blueCrystal.png", 0, 0, 0, 0, 0.05));
    // SIBUR
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/greenCrystal.obj",
                         "gui/assets/3Delements/greenCrystal.png", 0, 0, 0, 0, 0.05));
    // MENDIANE
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/whiteCrystal.obj",
                         "gui/assets/3Delements/whiteCrystal.png", 0, 0, 0, 0, 0.01));
    // PHIRAS
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/greenCrystal.obj",
                         "gui/assets/3Delements/redCrystal.png", 0, 0, 0, 0, 0.05));
    // THYSTAME
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/redCrystal.obj",
                         "gui/assets/3Delements/blueCrystal.png", 0, 0, 0, 0, 0.05));
    // PLAYER
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/toothless.obj",
                         "gui/assets/3Delements/food.png", 0, 0, 0, 0, 0.01));
    // EGG
    _models.emplace_back(std::make_shared<Raylib::Model3D>("gui/assets/3Delements/egg.obj",
                         "gui/assets/3Delements/food.png", 0, 0, 0, 0, 0.1));
    _models[FOOD]->setRotation(90);
}

void Zappy::Game::createMap()
{
    for (int i = 0; i < _mapSize.y; i++)
        for (int j = 0; j < _mapSize.x; j++)
            _tiles.emplace_back(j, i, _mapSize, _models);
}
