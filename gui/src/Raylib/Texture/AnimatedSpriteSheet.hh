/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AnimatedSpriteSheet
*/


#pragma once

#include "Texture.hh"
#include <iostream>
#include <raylib.h>

#include "../Shapes/RectangleEnc.hh"

namespace Raylib {
    class AnimatedSpriteSheet : public Texture {
    public:
        AnimatedSpriteSheet(const std::string &path, std::size_t nbframes,
                    std::size_t animationFramerate, std::size_t nbCol,
                    std::size_t nbRow = 1, double posx = 0, double posy = 0,
                    double rotation = 0, double scale = 1);
        ~AnimatedSpriteSheet();
        void DrawSpriteSheet();
        void updateFrame();
    protected:
        std::size_t _nbFrames;
        std::size_t _currentFrame;
        double _framerate;
        double _timeSinceLastFrame;
        Vector2 _spriteSheetSize;
        Vector2 _frameSize;
        RectangleEnc _frameRec;
    };
}
