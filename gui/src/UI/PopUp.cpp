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
    _texture("gui/assets/infoPopUpRight.png"), _info(15), _isOpen(false), _type(TILETYPE)
{
    Texture2D texture = _texture.GetTexture();
    double scale = (Raylib::Screen::myGetScreenHeight() * 0.9) / texture.height;

    _texture.setScale(scale);
    _texture.setPosition(Raylib::Screen::myGetScreenWidth() - texture.width * scale,
                         (Raylib::Screen::myGetScreenHeight() - texture.height * scale) / 2);

    _position = _texture.getPosition();
    _size = {static_cast<float>(texture.width * scale),
             static_cast<float>(texture.height * scale)};
    for (int i = 0; i < 15; i++)
        _info[i] = std::unique_ptr<Raylib::Text>(new Raylib::Text("", 40,
        "gui/assets/Futura Condensed Medium.ttf", _position.x + _size.x * 0.1,
        _position.y + _size.y * ((i + 1) * 0.05), 2, WHITE, Raylib::PIXEL, Raylib::LEFT));
}

Zappy::PopUp::~PopUp()
{
}

void Zappy::PopUp::setInfo(const Player &player)
{
    auto inventory = player.getInventory();

    _info[PLAYERID]->setText(TextFormat("Player #%u", player.getId()));
    _info[PLAYERINFO]->setText("Info:");
    _info[PLAYERLEVEL]->setText(TextFormat("   Level: %d", player.getLevel()));
    _info[PLAYERTEAM]->setText(TextFormat("   Team: %s", player.getTeam().c_str()));
    _info[PLAYERPOSITION]->setText(TextFormat("   Position: %.0f-%.0f",
         player.getPosition().y + 1, player.getPosition().x + 1));
    _info[PLAYERINVENTORY]->setText("Inventory:");
    _info[PLAYERINVENTORY + 1]->setText(TextFormat(" - Food: %d", inventory[FOOD]));
    _info[PLAYERINVENTORY + 2]->setText(TextFormat(" - Linemate: %d", inventory[LINEMATE]));
    _info[PLAYERINVENTORY + 3]->setText(TextFormat(" - Deraumere: %d", inventory[DERAUMERE]));
    _info[PLAYERINVENTORY + 4]->setText(TextFormat(" - Sibur: %d", inventory[SIBUR]));
    _info[PLAYERINVENTORY + 5]->setText(TextFormat(" - Mendiane: %d", inventory[MENDIANE]));
    _info[PLAYERINVENTORY + 6]->setText(TextFormat(" - Phiras: %d", inventory[PHIRAS]));
    _info[PLAYERINVENTORY + 7]->setText(TextFormat(" - Thystame: %d", inventory[THYSTAME]));
    _isOpen = true;
    _type = PLAYERTYPE;
}

void Zappy::PopUp::setInfo(const Tiles &tile, std::size_t playersOnTile, std::size_t eggsOnTile)
{
    auto resources = tile.getResources();

    _info[TITLE]->setText(TextFormat("Tile %.0f-%.0f", tile.getIndex().y + 1, tile.getIndex().x + 1));
    _info[RESOURCES]->setText("Resources:");
    _info[RESOURCES + 1]->setText(TextFormat(" - Food: %d", resources[FOOD]));
    _info[RESOURCES + 2]->setText(TextFormat(" - Linemate: %d", resources[LINEMATE]));
    _info[RESOURCES + 3]->setText(TextFormat(" - Deraumere: %d", resources[DERAUMERE]));
    _info[RESOURCES + 4]->setText(TextFormat(" - Sibur: %d", resources[SIBUR]));
    _info[RESOURCES + 5]->setText(TextFormat(" - Mendiane: %d", resources[MENDIANE]));
    _info[RESOURCES + 6]->setText(TextFormat(" - Phiras: %d", resources[PHIRAS]));
    _info[RESOURCES + 7]->setText(TextFormat(" - Thystame: %d", resources[THYSTAME]));
    _info[PLAYERSONTILE]->setText(TextFormat("Players on tile: %d", playersOnTile));
    _info[EGGSONTILE]->setText(TextFormat("Eggs on tile: %d", eggsOnTile));
    _isOpen = true;
    _type = TILETYPE;
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
    if (_type == PLAYERTYPE)
        for (std::size_t i = 0; i <= PLAYERINVENTORY + 7; i++)
            _info[i]->TextDraw();
    else if (_type == TILETYPE)
        for (std::size_t i = 0; i <= EGGSONTILE; i++)
            _info[i]->TextDraw();
}

bool Zappy::PopUp::Hits(Vector2 mousePos)
{
    return CheckCollisionPointRec(mousePos, {_position.x, _position.y, _size.x, _size.y});
}
