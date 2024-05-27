/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** FontEnc
*/

#include "FontEnc.hh"

Raylib::FontEnc::FontEnc(std::string fontName)
{
    CreateFont(fontName);
}

Raylib::FontEnc::~FontEnc()
{
    DestroyFont();
}

Font Raylib::FontEnc::getFont()
{
    return _font;
}

extern "C" {
    void Raylib::FontEnc::CreateFont(std::string fontName)
    {
        _font = LoadFont(fontName.c_str());
    }

    void Raylib::FontEnc::DestroyFont()
    {
        UnloadFont(_font);
    }
}
