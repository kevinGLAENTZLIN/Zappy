/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Button
*/

#include "Button.hh"
#include "../Raylib/Raylib.hh"

Zappy::Button::Button(const std::size_t &posX, const std::size_t &posY, const std::string &assetPath,
    const std::string &text, const std::string &font):
    _btnAction(0), _btnTexture(assetPath, 3, 1, 3, posX, posY)
{
    double frameHeight = _btnTexture.GetTexture().height / 3;

    _btnBounds.setSize(_btnTexture.GetTexture().width, frameHeight);
    _btnBounds.setPosition(_btnTexture.getPosition().x, _btnTexture.getPosition().y);
    std::size_t textPosX = _btnTexture.getPosition().x + (_btnTexture.GetTexture().width / 2);
    std::size_t textPosY = _btnTexture.getPosition().y + (frameHeight / 2);
    _text = std::make_unique<Raylib::Text>(text, 70, font, textPosX, textPosY, 2, BLACK, Raylib::PIXEL);
}

Zappy::Button::~Button()
{}

void Zappy::Button::Event()
{
    Vector2 mousePos = Raylib::Event::myGetMousePosition();
    _btnTexture.updateFrame(0);

    if (Raylib::Event::myCheckCollisionPointRec(mousePos, _btnBounds) == true) {
        _btnTexture.updateFrame(1);
        if (Raylib::Event::myIsMouseButtonDown(MOUSE_BUTTON_LEFT) == true)
            _btnTexture.updateFrame(2);
        if (Raylib::Event::myIsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            _btnAction = true;
    }
}

bool Zappy::Button::IsButtonPressed()
{
    if (_btnAction == true) {
        _btnAction = false;
        return true;
    }
    return false;
}

void Zappy::Button::Draw()
{
    _btnTexture.DrawSpriteSheet();
    _text->TextDraw();
}
