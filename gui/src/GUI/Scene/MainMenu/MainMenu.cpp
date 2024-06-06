/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** MainMenu
*/

#include "MainMenu.hh"

Zappy::MainMenu::MainMenu(std::shared_ptr<CommonElements> commonElements):
    _commonElements(commonElements), _playBtn(50, 60, "gui/assets/Button.png", "PLAY", "gui/assets/Futura Condensed Medium.ttf"),
    _optionBtn(50, 73, "gui/assets/Button.png", "OPTION", "gui/assets/Futura Condensed Medium.ttf"),
    _quitBtn(50, 86, "gui/assets/Button.png", "QUIT", "gui/assets/Futura Condensed Medium.ttf"),
    _guiSock(), _logo("gui/assets/logo.png", 50, 25, 0, 0.5)
{
    _commonElements->setConnect(false);
}

Zappy::MainMenu::~MainMenu()
{}

void Zappy::MainMenu::computeLogic()
{
    _playBtn.Event();
    if (_playBtn.IsButtonPressed()) {
        if (_commonElements->getConnect() != true) {
            _commonElements->setSocket(_guiSock.createSocket(_commonElements->getPort(), _commonElements->getIp()));
            _commonElements->setConnect(true);
        }
        _commonElements->setCurrentScene(2);
    }
    _optionBtn.Event();
    if (_optionBtn.IsButtonPressed())
        _commonElements->setCurrentScene(1);
    _quitBtn.Event();
    if (_quitBtn.IsButtonPressed())
        exit(0);
}

void Zappy::MainMenu::displayElements(void)
{
    _playBtn.Draw();
    _optionBtn.Draw();
    _quitBtn.Draw();
    _logo.DrawTexture();
    // _texture.DrawTexture();
}
