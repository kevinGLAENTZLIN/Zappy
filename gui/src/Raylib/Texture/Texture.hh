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
        Texture(const std::string &path, double posX = 0, double posY = 0,
                double rotation = 0, double scale = 1);
        ~Texture();
        Texture2D GetTexture() const;
        Vector2 getPosition() const;
        void DrawTexture();
    protected:
        void createTexture(const std::string &path);
        void destroyTexture();
        Texture2D _texture;
        Vector2 _position;
        double _rotation;
        double _scale;
    };
}
