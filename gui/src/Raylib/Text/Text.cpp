/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Text
*/

#include "Text.hh"
#include <raylib.h>

Raylib::Text::Text(const std::string &text, const std::size_t &textSize,
                   const FontEnc &font, const double &posX, const double &posY,
                   const double &spacing, const Color &color,
                   const std::size_t &textAlignment):
    _text(text), _textSize(textSize), _font(font), _spacing(spacing), _textColor(color)
{
    float posPixelX = Screen::myGetScreenWidth() * (posX / 100);
    float posPixelY = Screen::myGetScreenHeight() * (posY / 100) - getTextHeight() / 2;

    if (textAlignment == RIGHT)
        posPixelX -= getTextWidth();
    if (textAlignment == CENTER)
        posPixelX -= getTextWidth() / 2;
    _position = (Vector2){posPixelX, posPixelY};
}

Raylib::Text::Text(const std::string &text, const std::size_t &textSize,
                   const std::string &font, const double &posX, const double &posY,
                   const double &spacing, const Color &color,
                   const std::size_t &textAlignment):
    _text(text), _textSize(textSize), _font(font), _spacing(spacing), _textColor(color)
{
    float posPixelX = Screen::myGetScreenWidth() * (posX / 100);
    float posPixelY = Screen::myGetScreenHeight() * (posY / 100);

    if (textAlignment == RIGHT)
        posPixelX -= getTextWidth();
    if (textAlignment == CENTER)
        posPixelX -= getTextWidth() / 2;
    _position = (Vector2){posPixelX, posPixelY};
}

Raylib::Text::~Text()
{}

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
