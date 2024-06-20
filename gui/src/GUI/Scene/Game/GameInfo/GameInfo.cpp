/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** GameInfo
*/

#include "GameInfo.hh"
#include <string>

Zappy::GameInfo::GameInfo():
    _background("gui/assets/GameInfo.png")
{
    _scale = (Raylib::Screen::myGetScreenWidth() / 4.0f) / _background.WIDTH;
    _background.setScale(_scale);
    _background.setPosition(0, (Raylib::Screen::myGetScreenHeight() -
                            (_background.HEIGHT * _scale)) / 2.0f);
    setUpTexts();
}

Zappy::GameInfo::~GameInfo()
{
}

void Zappy::GameInfo::updateTitle(std::size_t nbPlayers)
{
    _title->setText("Players: " + std::to_string(nbPlayers));
}

void Zappy::GameInfo::updateValues(std::vector<std::size_t> values)
{
    for (std::size_t i = 0; i < values.size(); i++) {
        _values[i]->setText("Lvl " + std::to_string(i + 1) + ": " + std::to_string(values[i]));
    }
}

void Zappy::GameInfo::display()
{
    _background.DrawTexture();
    _title->TextDraw();
    for (auto &value : _values) {
        value->TextDraw();
    }
}

void Zappy::GameInfo::setUpTexts()
{
    double offset = _background.WIDTH * _scale * OFFSET;
    double textureHeight = _background.HEIGHT * _scale;
    double textureWidth = _background.WIDTH * _scale;
    double infoPosEven = (textureWidth - offset) * (2 / 6.0f) + offset;
    double infoPosOdd = (textureWidth - offset) * (4 / 6.0f) + offset;
    double infoPosY = _background.getPosition().y + textureHeight * 0.10f;

    _title = std::make_shared<Raylib::Text>("Players: 0", 50,
             "gui/assets/Futura Condensed Medium.ttf", (textureWidth - offset)
             / 2.0f + offset, _background.getPosition().y + textureHeight * 0.1f,
             0, WHITE, Raylib::TextPosFormat::PIXEL, Raylib::TextAlignment::CENTER);
    for (std::size_t i = 0; i < 8; i++)
        if (i % 2 == 0) {
            infoPosY += textureHeight * 0.20f;
            _values.push_back(std::make_shared<Raylib::Text>("Lvl " + std::to_string(i + 1) + ": 0",
                35, "gui/assets/Futura Condensed Medium.ttf", infoPosEven, infoPosY,
                0, WHITE, Raylib::TextPosFormat::PIXEL, Raylib::TextAlignment::CENTER));
        } else
            _values.push_back(std::make_shared<Raylib::Text>("Lvl " + std::to_string(i + 1) + ": 0",
                35, "gui/assets/Futura Condensed Medium.ttf", infoPosOdd, infoPosY,
                0, WHITE, Raylib::TextPosFormat::PIXEL, Raylib::TextAlignment::CENTER));
}
