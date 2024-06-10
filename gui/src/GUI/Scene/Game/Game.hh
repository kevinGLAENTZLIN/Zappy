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
#include "Elements.hh"
#include "Network/Network.hh"
#include "../IScene.hh"
#include "../../../UI/PopUp.hh"
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

        void updateTile(std::size_t x, std::size_t y,
                        std::vector<std::size_t> resources);

        void addPlayer(std::size_t id, std::size_t x, std::size_t y,
                       std::size_t playerOrientation, std::size_t level,
                       std::string teamName);
        void updatePlayerPosition(std::size_t id, std::size_t x, std::size_t y,
                                  std::size_t playerOrientation);
        void updatePlayerLevel(std::size_t id, std::size_t level);
        void updatePlayerInventory(std::size_t id, std::vector<std::size_t> resources);
        void playerDeath(std::size_t id);
    private:
        void userInteractions();
        void loadModels();

        void createMap();

        std::shared_ptr<CommonElements> _commonElements;
        std::vector<std::shared_ptr<Raylib::Model3D>> _models;
        std::vector<Tiles> _tiles;
        std::vector<Player> _players;
        std::size_t _timerSizeT;
        double _timer;
        Vector2 _mapSize;
        bool _mapSizeQuery;
        double _tickTime;
        Network _network;
        PopUp _popUp;
    };
}
