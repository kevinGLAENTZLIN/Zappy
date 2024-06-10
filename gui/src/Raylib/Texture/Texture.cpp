/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Texture
*/

#include "Texture.hh"
#include <raylib.h>
#include "../Screen/Screen.hh"

Raylib::Texture::Texture(const std::string &fileName, float posX, float posY,
                float rotation, float scale):
    _rotation(rotation), _scale(scale)
{
    float posPixelX;
    float posPixelY;

    createTexture(fileName);
    _percentPos = {posX, posY};
    posPixelX = Screen::myGetScreenWidth() * (posX / 100) - (_texture.width * scale) / 2.0f;
    posPixelY = Screen::myGetScreenHeight() * (posY / 100) - (_texture.height * scale) / 2.0f;
    _position = {posPixelX, posPixelY};
}

Raylib::Texture::~Texture()
{
    destroyTexture();
}

Texture2D Raylib::Texture::GetTexture() const
{
    return _texture;
}

Vector2 Raylib::Texture::getPosition() const
{
    return _position;
}

std::pair<float, float> Raylib::Texture::getPercentPos() const
{
    return _percentPos;
}

void Raylib::Texture::setPosition(float x, float y)
{
    _position = {x, y};
}

void Raylib::Texture::setScale(double scale)
{
    _scale = scale;
}

extern "C" {
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
