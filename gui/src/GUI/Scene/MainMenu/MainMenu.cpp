/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** MainMenu
*/

#include "MainMenu.hh"
#include <raylib.h>

Zappy::MainMenu::MainMenu(std::shared_ptr<CommonElements> commonElements):
    _commonElements(commonElements), _playBtn(50, 60, "gui/assets/Button.png", "PLAY", "gui/assets/Futura Condensed Medium.ttf"),
    _optionBtn(50, 73, "gui/assets/Button.png", "OPTION", "gui/assets/Futura Condensed Medium.ttf"),
    _quitBtn(50, 86, "gui/assets/Button.png", "QUIT", "gui/assets/Futura Condensed Medium.ttf"),
    _guiSock(), _logo("gui/assets/toothless-dancing.png", 270, 24, 15, 18, 50, 25),
    _popUp(false), _popUpBack("gui/assets/InfoBox.png", 50, 50, 0, 0.2),
    _popUpText("Connection Error", 80, "gui/assets/Futura Condensed Medium.ttf", _popUpBack.getPercentPos().first, _popUpBack.getPercentPos().second - 8, 2, WHITE, Raylib::PERCENT),
    _closePopUpText("Press space to close", 80, "gui/assets/Futura Condensed Medium.ttf", _popUpBack.getPercentPos().first, _popUpBack.getPercentPos().second + 7, 2, WHITE, Raylib::PERCENT)
{
    _commonElements->setConnect(false);
}

Zappy::MainMenu::~MainMenu()
{}

void Zappy::MainMenu::computeLogic()
{
    _commonElements->getMap()->setRotation(_commonElements->getMap()->getRotation() + 0.5);
    if (Raylib::Event::myIsKeyDown(KEY_SPACE) && _popUp == true)
        _popUp = false;
    if (_popUp == true)
        return;
    _playBtn.Event();
    if (_playBtn.IsButtonPressed()) {
        if (_commonElements->getConnect() != true) {
            checkConnection();
        } else {
            _commonElements->setCurrentScene(2);
        }
        _commonElements->getMap()->setRotation(0);
    }
    _optionBtn.Event();
    if (_optionBtn.IsButtonPressed()) {
        _commonElements->setCurrentScene(1);
        _commonElements->setOldScene(0);
    }
    _quitBtn.Event();
    if (_quitBtn.IsButtonPressed())
        _commonElements->setExit(true);
}

void Zappy::MainMenu::displayElements(void)
{
    _commonElements->getCamera().begin3DMode();
        _commonElements->getMap()->ModelDraw();
    _commonElements->getCamera().end3DMode();
    _playBtn.Draw();
    _optionBtn.Draw();
    _quitBtn.Draw();
    _logo.DrawSpriteSheet();
    if (_popUp)
        displayPopUp();
}

void Zappy::MainMenu::checkConnection()
{
    try {
        _commonElements->setSocket(_guiSock.createSocket(_commonElements->getPort(), _commonElements->getIp()));
        _commonElements->setConnect(true);
        _commonElements->setCurrentScene(2);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        _popUp = true;
    }
}

void Zappy::MainMenu::displayPopUp()
{
    _popUpBack.DrawTexture();
    _popUpText.TextDraw();
    _closePopUpText.TextDraw();
}
