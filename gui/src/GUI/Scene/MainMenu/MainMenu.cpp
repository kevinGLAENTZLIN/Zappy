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
    _guiSock(), _logo("gui/assets/logo.png", 50, 25, 0, 0.5), _popUp(false),
    _popUpBack("gui/assets/InfoBox.png", 50, 50, 0, 0.2),
    _popUpText("Connection Error", 80, "gui/assets/Futura Condensed Medium.ttf", _popUpBack.getPercentPos().first, _popUpBack.getPercentPos().second - 8, 2, WHITE, Raylib::PERCENT),
    _closePopUpText("Press space to close", 80, "gui/assets/Futura Condensed Medium.ttf", _popUpBack.getPercentPos().first, _popUpBack.getPercentPos().second + 7, 2, WHITE, Raylib::PERCENT)
{
    _commonElements->setConnect(false);
}

Zappy::MainMenu::~MainMenu()
{}

void Zappy::MainMenu::computeLogic()
{
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
    }
    _optionBtn.Event();
    if (_optionBtn.IsButtonPressed()) {
        _commonElements->setCurrentScene(1);
        _commonElements->setOldScene(0);
    }
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
