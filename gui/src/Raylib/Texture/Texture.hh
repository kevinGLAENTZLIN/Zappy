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
        Texture(const std::string &path, double posX, double posY,
                double rotation, double scale);
        ~Texture();
        void DrawTexture();
    private:
        void createTexture(const std::string &path);
        void destroyTexture();
        Texture2D _texture;
        Vector2 _position;
        double _rotation;
        double _scale;
    };
}
