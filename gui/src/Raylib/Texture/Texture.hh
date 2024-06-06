/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Texture
*/


#pragma once

#include <iostream>
#include <raylib.h>

namespace Raylib {
    class Texture {
    public:
        // INFO: the position in the constructor are specified in % of the screen
        Texture(const std::string &path, float posX = 0, float posY = 0,
                float rotation = 0, float scale = 1);
        ~Texture();
        Texture2D GetTexture() const;
        std::pair<float, float> getPercentPos() const;
        Vector2 getPosition() const;
        void setPosition(float x, float y);
        void DrawTexture();
    protected:
        void createTexture(const std::string &path);
        void destroyTexture();
        Texture2D _texture;
        std::pair<float, float> _percentPos;
        Vector2 _position;
        double _rotation;
        double _scale;
    };
}
