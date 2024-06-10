/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Text
*/


#pragma once

#include <iostream>
#include <raylib.h>

#include "../Screen/Screen.hh"
#include "FontEnc.hh"

namespace Raylib {

    enum TextAlignment {
        LEFT,
        RIGHT,
        CENTER,
    };

    enum TextFormat {
        PIXEL,
        PERCENT,
    };

    class Text {
    public:
        // INFO: the position in the constructor are specified in % of the screen
        Text(const std::string &text, const std::size_t &textSize, const std::string &font,
             const double &posX, const double &posY, const double &spacing,
             const Color &color, const TextFormat &textFormat, const TextAlignment &textAlign = CENTER);
        ~Text();
        void TextDraw();
        double getTextWidth();
        double getTextHeight();

    private:
        std::string _text;
        std::size_t _textSize;
        FontEnc _font;
        Vector2 _position;
        double _spacing;
        Color _textColor;
    };
}
