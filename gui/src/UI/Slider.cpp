/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Slider
*/

#include "Slider.hh"

Zappy::Slider::Slider(const std::string &title, float posX, float posY, float value):
    _size(1.5), _barTexture("gui/assets/slider-bar.png", posX, posY, 0, 0.3),
    _title(title, 80, "gui/assets/Futura Condensed Medium.ttf", _barTexture.getPercentPos().first, _barTexture.getPercentPos().second - 6, 2, WHITE, Raylib::PERCENT),
    _cursorTexture("gui/assets/cursor.png", posX, posY, 0, 0.25), _sliderValue(value)
{
    _cursorRec.setSize(_cursorTexture.GetTexture().width * 0.25, _cursorTexture.GetTexture().height * 0.25);
    _cursorRec.setPosition(_cursorTexture.getPosition().x, _cursorTexture.getPosition().y);
    _barRec.setSize((_barTexture.GetTexture().width - 320) * 0.3, _barTexture.GetTexture().height * 0.3);
    _barRec.setPosition(_barTexture.getPosition().x + 50, _barTexture.getPosition().y);
}

Zappy::Slider::~Slider()
{}

void Zappy::Slider::computeLogic()
{
    Vector2 mousePos = Raylib::Event::myGetMousePosition();

    if (Raylib::Event::myCheckCollisionPointRec(mousePos, _cursorRec) == true || _cursorAction == true) {
            _cursorAction = true;
        if (Raylib::Event::myIsMouseButtonDown(MOUSE_BUTTON_LEFT) == true && CheckCollisionPointRec({mousePos.x, static_cast<float>(_barRec.getPosition().second)}, _barRec.getRectangle()) &&
            !CheckCollisionPointRec({mousePos.x, static_cast<float>(_barRec.getPosition().second) - 10}, _barRec.getRectangle())) {
            _cursorTexture.setPosition(mousePos.x - (_cursorTexture.GetTexture().width * 0.25) / 2,
                                       _cursorTexture.getPosition().y);
            _cursorRec.setPosition(mousePos.x - (_cursorTexture.GetTexture().width * 0.25) / 2,
                                   _cursorTexture.getPosition().y);
            _sliderValue = (_cursorRec.getPosition().first - _barRec.getPosition().first) / (_barRec.getRectangle().width);
            if (_sliderValue < 0)
                _sliderValue = 0;
        }
        if (Raylib::Event::myIsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            _cursorAction = false;
    }
}

bool Zappy::Slider::isCursorPressed()
{
    return _cursorAction;
}

void Zappy::Slider::displayElements()
{
    _title.TextDraw();
    _barTexture.DrawTexture();
    _cursorTexture.DrawTexture();
}

float Zappy::Slider::getValue() const
{
    return _sliderValue;
}
