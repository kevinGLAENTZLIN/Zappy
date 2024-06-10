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
    class PopUp {
    public:
        PopUp();
        ~PopUp();

        void setInfo(const Player &player);
        void setInfo(const Tiles &tile);
        void setStatus(bool status);

        bool getStatus() const;

        void Draw();
        bool Hits(Vector2 mousePos);
    private:
        void addInfoMultithread(const std::string &text, const std::size_t &textSize,
                           const double &posX, const double &posY,
                           const double &spacing, const Color &color,
                           const Raylib::TextFormat &textFormat,
                           const Raylib::TextAlignment &textAlign = Raylib::CENTER);

        std::mutex _mutex;
        Vector2 _position;
        Vector2 _size;
        Raylib::Texture _texture;
        std::vector<std::unique_ptr<Raylib::Text>> _info;
        bool _isOpen;
    };
}
