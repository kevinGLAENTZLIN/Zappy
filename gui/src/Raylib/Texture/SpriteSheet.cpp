/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** SpriteSheet
*/

#include "SpriteSheet.hh"

Raylib::SpriteSheet::SpriteSheet(const std::string &path, std::size_t nbframes,
                                 std::size_t nbCol, std::size_t nbRow, double posX, double posY,
                                 double rotation, double scale):
    Texture(path, posX, posY, rotation, scale), _nbFrames(nbframes), _currentFrame(0),
    _spriteSheetSize({static_cast<float>(nbCol), static_cast<float>(nbRow)})
{
    _frameSize = {(_texture.width * static_cast<float>(scale)) / _spriteSheetSize.x, (_texture.height * static_cast<float>(scale)) / _spriteSheetSize.y};
    _frameRec.setSize(_frameSize.x, _frameSize.y);
    _position.x = GetScreenWidth() * (posX / 100) - _frameSize.x / 2.0f;
    _position.y = GetScreenHeight() * (posY / 100) - _frameSize.y / 2.0f;
}

Raylib::SpriteSheet::~SpriteSheet()
{}

void Raylib::SpriteSheet::DrawSpriteSheet()
{
    DrawTextureRec(_texture, _frameRec.getRectangle(), _position, WHITE);
}

void Raylib::SpriteSheet::updateFrame(std::size_t frame)
{
    std::size_t newPosX = _frameRec.getSize().first * (frame % static_cast<std::size_t>(_spriteSheetSize.x));
    std::size_t newPosY = 0;

    newPosY = _frameRec.getSize().second * static_cast<std::size_t>(frame % static_cast<std::size_t>(_spriteSheetSize.y));
    _frameRec.setPosition(newPosX, newPosY);
}
