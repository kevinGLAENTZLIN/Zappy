/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Game
*/


#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Map/Tiles.hh"
#include "Player/Player.hh"
#include "Player/Egg.hh"
#include "Elements.hh"
#include "Network/Network.hh"
#include "GameInfo/GameInfo.hh"
#include "../IScene.hh"
#include "../../../UI/PopUp.hh"
#include "./PauseMenu/PauseMenu.hh"
#include "../../../Raylib/Raylib.hh"
#include "../../CommonElements/CommonElements.hh"
#include "../../../Utils/GuiSocket.hh"

namespace Zappy {
    class Game : public IScene {
    public:
        Game(std::shared_ptr<CommonElements> commonElements);
        ~Game() override;

        void computeLogic() override;
        void displayElements(void) override;

        void setMapSize(std::size_t x, std::size_t y);
        void setTickTime(std::size_t nbTicksPerSecond);

        Vector2 getPlayerPosition(std::size_t id);

        void updateTile(std::size_t x, std::size_t y,
                        std::vector<std::size_t> resources);
        void addEgg(std::size_t id, std::size_t x, std::size_t y);
        void addEgg(std::size_t id, std::size_t playerID);
        void removeEgg(std::size_t id);
        void addPlayer(std::size_t id, std::size_t x, std::size_t y,
                       std::size_t playerOrientation, std::size_t level,
                       std::string teamName);
        void updateStatus(std::size_t id, playerStatus status);
        void updateStatus(std::size_t x, std::size_t y, playerStatus status);
        void updatePlayerPosition(std::size_t id, std::size_t x, std::size_t y,
                                  std::size_t playerOrientation);
        void updatePlayerLevel(std::size_t id, std::size_t level);
        void updatePlayerInventory(std::size_t id, std::vector<std::size_t> resources);
        void playerDeath(std::size_t id);
        void playerBroadcast(std::size_t id, const std::string &message);
        void addTeam(std::string teamName);
    private:
        std::size_t findPlayersFromCoordinates(Vector2 coordinates);
        std::size_t findEggsFromCoordinates(Vector2 coordinates);
        std::vector<std::size_t> findAllLevels();
        void userInteractions(Raylib::Camera &cam);
        void findMapModelSize();
        void loadModels();

        void createMap();

        std::shared_ptr<CommonElements> _commonElements;
        std::vector<std::shared_ptr<Raylib::Model3D>> _models;
        std::vector<Tiles> _tiles;
        std::vector<Player> _players;
        std::vector<Egg> _eggs;
        std::size_t _timerSizeT;
        double _timer;
        Vector2 _mapSize;
        bool _mapSizeQuery;
        double _tickTime;
        Network _network;
        PopUp _popUp;
        PauseMenu _pauseMenu;
        std::size_t _selectedObject;
        PopUpType _selectedObjectType;
        GameInfo _gameInfo;
        Raylib::Skybox _skybox;
    };
}
