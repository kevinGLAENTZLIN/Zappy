/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** OptionMenu
*/

#include "OptionMenu.hh"

Zappy::OptionMenu::OptionMenu(std::shared_ptr<CommonElements> commonElements):
    _commonElements(commonElements), _backBtn(8, 5, "gui/assets/button.png", "BACK", "gui/assets/DURALITH.ttf")
{}

Zappy::OptionMenu::~OptionMenu()
{}

void Zappy::OptionMenu::computeLogic()
{
    _backBtn.Event();
    if (_backBtn.IsButtonPressed())
        _commonElements->setCurrentScene(0);
}

void Zappy::OptionMenu::displayElements(void)
{
    _backBtn.Draw();
}
