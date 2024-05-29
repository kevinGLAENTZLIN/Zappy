/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** SpriteSheet
*/


#pragma once

#include "Texture.hh"
#include <iostream>
#include <raylib.h>

#include "../Shapes/RectangleEnc.hh"

namespace Raylib {
    class SpriteSheet : public Texture {
    public:
        SpriteSheet(const std::string &path, std::size_t nbframes,
                    std::size_t nbCol, std::size_t nbRow = 1, double posx = 0,
                    double posy = 0, double rotation = 0, double scale = 1);
        ~SpriteSheet();
        void DrawSpriteSheet();
        void updateFrame(std::size_t frame);
    protected:
        std::size_t _nbFrames;
        std::size_t _currentFrame;
        Vector2 _spriteSheetSize;
        Vector2 _frameSize;
        RectangleEnc _frameRec;
    };
}
