/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** PopUp
*/

#include "PopUp.hh"
#include <memory>
#include <raylib.h>

Zappy::PopUp::PopUp():
    _texture("gui/assets/infoPopUpRight.png")
{
    Texture2D texture = _texture.GetTexture();
    double scale = (Raylib::Screen::myGetScreenHeight() * 0.9) / texture.height;

    _texture.setScale(scale);
    _texture.setPosition(Raylib::Screen::myGetScreenWidth() - texture.width * scale,
                         (Raylib::Screen::myGetScreenHeight() - texture.height * scale) / 2);

    _position = _texture.getPosition();
    _size = {static_cast<float>(texture.width * scale),
             static_cast<float>(texture.height * scale)};
    _isOpen = false;
}

Zappy::PopUp::~PopUp()
{
}

void Zappy::PopUp::setInfo(const Player &player)
{
    _info.clear();
    _info.push_back(std::unique_ptr<Raylib::Text>(new Raylib::Text(TextFormat("Player #%d",
                       player.getId()), 20, "gui/assets/Futura Condensed Medium.ttf",
                       _position.x + _size.x / 2, _position.y * 0.9, 2, WHITE, Raylib::PIXEL)));
    _isOpen = true;
}

void Zappy::PopUp::setInfo(const Tiles &tile)
{
    auto resources = tile.getResources();

    _info.clear();
    _info.push_back(std::unique_ptr<Raylib::Text>(new Raylib::Text(TextFormat("Tile %.0f-%.0f",
                       tile.getIndex().y + 1, tile.getIndex().x + 1), 60, "gui/assets/Futura Condensed Medium.ttf",
                       _position.x + _size.x / 2, _position.y + _size.y * 0.05, 2, WHITE, Raylib::PIXEL)));
    _info.push_back(std::unique_ptr<Raylib::Text>(new Raylib::Text("Resources:", 40,
                       "gui/assets/Futura Condensed Medium.ttf", _position.x + _size.x * 0.1,
                       _position.y + _size.y * 0.15, 2, WHITE, Raylib::PIXEL, Raylib::LEFT)));
    _info.push_back(std::unique_ptr<Raylib::Text>(new Raylib::Text(TextFormat(" - Food: %d", resources[FOOD]),
                       40, "gui/assets/Futura Condensed Medium.ttf", _position.x + _size.x * 0.1,
                       _position.y + _size.y * 0.20, 2, WHITE, Raylib::PIXEL, Raylib::LEFT)));
    _info.push_back(std::unique_ptr<Raylib::Text>(new Raylib::Text(TextFormat(" - Linemate: %d", resources[LINEMATE]),
                       40, "gui/assets/Futura Condensed Medium.ttf", _position.x + _size.x * 0.1,
                       _position.y + _size.y * 0.25, 2, WHITE, Raylib::PIXEL, Raylib::LEFT)));
    _info.push_back(std::unique_ptr<Raylib::Text>(new Raylib::Text(TextFormat(" - Deraumere: %d", resources[DERAUMERE]),
                       40, "gui/assets/Futura Condensed Medium.ttf", _position.x + _size.x * 0.1,
                       _position.y + _size.y * 0.30, 2, WHITE, Raylib::PIXEL, Raylib::LEFT)));
    _info.push_back(std::unique_ptr<Raylib::Text>(new Raylib::Text(TextFormat(" - Sibur: %d", resources[SIBUR]),
                       40, "gui/assets/Futura Condensed Medium.ttf", _position.x + _size.x * 0.1,
                       _position.y + _size.y * 0.35, 2, WHITE, Raylib::PIXEL, Raylib::LEFT)));
    _info.push_back(std::unique_ptr<Raylib::Text>(new Raylib::Text(TextFormat(" - Mendiane: %d", resources[MENDIANE]),
                       40, "gui/assets/Futura Condensed Medium.ttf", _position.x + _size.x * 0.1,
                       _position.y + _size.y * 0.40, 2, WHITE, Raylib::PIXEL, Raylib::LEFT)));
    _info.push_back(std::unique_ptr<Raylib::Text>(new Raylib::Text(TextFormat(" - Phiras: %d", resources[PHIRAS]),
                       40, "gui/assets/Futura Condensed Medium.ttf", _position.x + _size.x * 0.1,
                       _position.y + _size.y * 0.45, 2, WHITE, Raylib::PIXEL, Raylib::LEFT)));
    _info.push_back(std::unique_ptr<Raylib::Text>(new Raylib::Text(TextFormat(" - Thystame: %d", resources[THYSTAME]),
                       40, "gui/assets/Futura Condensed Medium.ttf", _position.x + _size.x * 0.1,
                       _position.y + _size.y * 0.50, 2, WHITE, Raylib::PIXEL, Raylib::LEFT)));
    _isOpen = true;
}

void Zappy::PopUp::setStatus(bool status)
{
    _isOpen = status;
}

bool Zappy::PopUp::getStatus() const
{
    return _isOpen;
}

void Zappy::PopUp::Draw()
{
    if (_isOpen == false)
        return;
    _texture.DrawTexture();
    for (std::size_t i = 0; i < _info.size(); i++)
        _info[i]->TextDraw();
}

bool Zappy::PopUp::Hits(Vector2 mousePos)
{
    return CheckCollisionPointRec(mousePos, {_position.x, _position.y, _size.x, _size.y});
}
