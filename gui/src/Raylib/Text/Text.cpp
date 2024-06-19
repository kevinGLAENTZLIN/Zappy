/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Text
*/

#include "Text.hh"
#include <raylib.h>

Raylib::Text::Text(const std::string &text, const std::size_t &textSize,
                   const std::string &font, const double &posX, const double &posY,
                   const double &spacing, const Color &color, const TextPosFormat &textFormat,
                   const TextAlignment &textAlign):
    _text(text), _textSize(textSize), _font(font), _spacing(spacing), _textColor(color)
{
    float newPosX = posX;
    float newPosY = posY;

    if (textFormat == PERCENT) {
        newPosX = Screen::myGetScreenWidth() * (posX / 100);
        newPosY = Screen::myGetScreenHeight() * (posY / 100);
    }
    if (textAlign == RIGHT)
        newPosX -= getTextWidth();
    if (textAlign == CENTER)
        newPosX -= getTextWidth() / 2;
    newPosY -= getTextHeight() / 2;
    _position = (Vector2){newPosX, newPosY};
}

Raylib::Text::~Text()
{}

void Raylib::Text::setText(const std::string &text)
{
    _text = text;
}

extern "C" {
    void Raylib::Text::TextDraw()
    {
        DrawTextEx(_font.getFont(), _text.c_str(), _position, _textSize, _spacing,
                   _textColor);
    }

    double Raylib::Text::getTextWidth()
    {
        return MeasureTextEx(_font.getFont(), _text.c_str(), _textSize, _spacing).x;
    }

    double Raylib::Text::getTextHeight()
    {
        return MeasureTextEx(_font.getFont(), _text.c_str(), _textSize, _spacing).y;
    }
}
