/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** PopUp
*/


#pragma once

#include "../Raylib/Raylib.hh"
#include "../GUI/Scene/Game/Player/Player.hh"
#include "../GUI/Scene/Game/Map/Tiles.hh"
#include <mutex>

namespace Zappy {

    enum PopUpType {
        PLAYERTYPE,
        TILETYPE,
    };

    enum TILEINFO {
        TITLE = 0,
        RESOURCES = 1,
        PLAYERSONTILE = 9,
        EGGSONTILE = 10,
    };

    enum PLAYERINFO {
        PLAYERID,
        PLAYERINFO,
        PLAYERLEVEL,
        PLAYERTEAM,
        PLAYERPOSITION,
        PLAYERINVENTORY,
    };

    class PopUp {
    public:
        PopUp();
        ~PopUp();

        void setInfo(const Player &player);
        void setInfo(const Tiles &tile, std::size_t playersOnTile, std::size_t eggsOnTile);
        void setStatus(bool status);

        bool getStatus() const;

        void Draw();
        bool Hits(Vector2 mousePos);
    private:
        std::mutex _mutex;
        Vector2 _position;
        Vector2 _size;
        Raylib::Texture _texture;
        std::vector<std::unique_ptr<Raylib::Text>> _info;
        bool _isOpen;
        PopUpType _type;
    };
}
