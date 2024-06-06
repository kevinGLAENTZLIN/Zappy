/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Checkbox
*/

#include "Checkbox.hh"

Zappy::Checkbox::Checkbox(double posX, double posY, const std::string &title, Color textColor):
    _checkbox("gui/assets/Checkmark.png", posX, posY, 0, 0.5),
    _check("gui/assets/CheckmarkCheck.png", posX, posY, 0, 0.5),
    _checkRec(posX, posY, _checkbox.GetTexture().width , _checkbox.GetTexture().height, WHITE),
    _title(title,80, "gui/assets/Futura Condensed Medium.ttf", _checkbox.getPercentPos().first,  _checkbox.getPercentPos().second - 7, 2, textColor, Raylib::PERCENT), _checked(false)
{
    _checkRec.setSize(_checkbox.GetTexture().width * 0.5, _checkbox.GetTexture().height * 0.5);
    _checkRec.setPosition(_checkbox.getPosition().x, _checkbox.getPosition().y);
}

Zappy::Checkbox::~Checkbox()
{}

void Zappy::Checkbox::Event()
{
    Vector2 mousePos = Raylib::Event::myGetMousePosition();

    if (Raylib::Event::myCheckCollisionPointRec(mousePos, _checkRec) == true) {
        if (Raylib::Event::myIsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            _checked = !_checked;
    }
}

bool Zappy::Checkbox::isChecked() const
{
    return _checked;
}

void Zappy::Checkbox::Draw()
{
    _checkbox.DrawTexture();
    _title.TextDraw();
    if (_checked)
        _check.DrawTexture();
}
