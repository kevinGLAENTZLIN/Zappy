/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AnimatedSpriteSheet
*/

#include "AnimatedSpriteSheet.hh"

Raylib::AnimatedSpriteSheet::AnimatedSpriteSheet(const std::string &path, std::size_t nbframes,
                                std::size_t animationFramerate, std::size_t nbCol,
                                std::size_t nbRow, double posX, double posY,
                                double rotation, double scale):
    Texture(path, posX, posY, rotation, scale), _nbFrames(nbframes), _currentFrame(0),
    _framerate(1 / static_cast<double>(animationFramerate)), _timeSinceLastFrame(0),
    _spriteSheetSize({static_cast<float>(nbCol), static_cast<float>(nbRow)})
{
    _frameSize = {_texture.width / _spriteSheetSize.x, _texture.height / _spriteSheetSize.y};
    _frameRec.setSize(_frameSize.x, _frameSize.y);
    _position.x = GetScreenWidth() * (posX / 100) - _frameSize.x / 2.0f;
    _position.y = GetScreenHeight() * (posY / 100) - _frameSize.y / 2.0f;
}

Raylib::AnimatedSpriteSheet::~AnimatedSpriteSheet()
{}

void Raylib::AnimatedSpriteSheet::DrawSpriteSheet()
{
    _timeSinceLastFrame += GetFrameTime();
    if (_timeSinceLastFrame >= _framerate) {
        _timeSinceLastFrame = 0;
        updateFrame();
    }
    DrawTextureRec(_texture, _frameRec.getRectangle(), _position, WHITE);
}

void Raylib::AnimatedSpriteSheet::updateFrame()
{
    std::size_t newPosX = 0;
    std::size_t newPosY = _frameRec.getPosition().second;

    _currentFrame++;
    newPosX = _frameRec.getPosition().first + _frameSize.x;
    if (_currentFrame % static_cast<std::size_t>(_spriteSheetSize.x) == 0) {
        newPosX = 0;
        newPosY = _frameRec.getPosition().second + _frameSize.y;
    }
    _frameRec.setPosition(newPosX, newPosY);
}
