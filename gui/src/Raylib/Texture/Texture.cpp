/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Texture
*/

#include "Texture.hh"
#include <raylib.h>

Raylib::Texture::Texture(const std::string &fileName, double posX, double posY,
                double rotation, double scale):
    _rotation(rotation), _scale(scale)
{
    double posPixelX;
    double posPixelY;

    createTexture(fileName);
    posPixelX = GetScreenWidth() * (posX / 100) - _texture.width / 2.0f;
    posPixelY = GetScreenHeight() * (posY / 100) - _texture.height / 2.0f;
    _position = {static_cast<float>(posPixelX), static_cast<float>(posPixelY)};
}

extern "C" {
    Raylib::Texture::~Texture()
    {
        UnloadTexture(_texture);
    }

    void Raylib::Texture::DrawTexture()
    {
        DrawTextureEx(_texture, _position, _rotation, _scale, WHITE);
    }

    void Raylib::Texture::createTexture(const std::string &path)
    {
        _texture = LoadTexture(path.c_str());
    }

    void Raylib::Texture::destroyTexture()
    {
        UnloadTexture(_texture);
    }
}
