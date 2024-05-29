/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** FontEnc
*/


#pragma once

#include <raylib.h>
#include <iostream>

namespace Raylib {
    class FontEnc {
    public:
        FontEnc(std::string fontName);
        ~FontEnc();
        Font getFont();
    private:
        void CreateFont(std::string fontName);
        void DestroyFont();
        Font _font;
    };
}
