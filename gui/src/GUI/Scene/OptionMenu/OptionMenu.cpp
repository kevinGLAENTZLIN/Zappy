/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** OptionMenu
*/

#include "OptionMenu.hh"

Zappy::OptionMenu::OptionMenu(std::shared_ptr<CommonElements> commonElements):
    _commonElements(commonElements), _backBtn(50, 7, "gui/assets/Button.png", "BACK", "gui/assets/Futura Condensed Medium.ttf"),
    _backBox("gui/assets/box.png", 50, 55, 0, 0.15), _slider("VOLUME",50, 43), _fullscreenBtn(50, 60, "gui/assets/ButtonLight.png", "FULLSCREEN", "gui/assets/Futura Condensed Medium.ttf", WHITE),
    _showFPS(35, 83, "Show FPS", WHITE), _muteCheck(65, 83, "Mute", WHITE),
    _title("Options", 80, "gui/assets/Futura Condensed Medium.ttf", 50, 22, 2, WHITE, Raylib::PERCENT)
{}

Zappy::OptionMenu::~OptionMenu()
{}

void Zappy::OptionMenu::computeLogic()
{
    _commonElements->getMap()->setRotation(_commonElements->getMap()->getRotation() + 0.5);
    _backBtn.Event();
    if (_backBtn.IsButtonPressed()) {
        _commonElements->getMap()->setRotation(0);
        _commonElements->setCurrentScene(_commonElements->getOldScene());
    }
    _slider.computeLogic();
    if (_slider.isCursorPressed() && _commonElements->getMute() == false)
        _commonElements->getMusic().setVolume(_slider.getValue());
    _fullscreenBtn.Event();
    if (_fullscreenBtn.IsButtonPressed())
            ToggleFullscreen();
    _showFPS.Event();
    if (_showFPS.isChecked())
        _commonElements->setShowFPS(true);
    else
        _commonElements->setShowFPS(false);
    _muteCheck.Event();
    if (_muteCheck.isChecked()) {
        _commonElements->setMute();
        _commonElements->getMusic().setVolume(0);
    } else {
        _commonElements->setMute();
        _commonElements->getMusic().setVolume(_slider.getValue());
    }

}

void Zappy::OptionMenu::displayElements(void)
{
    _commonElements->getCamera().begin3DMode();
        _commonElements->getMap()->ModelDraw();
    _commonElements->getCamera().end3DMode();
    _backBtn.Draw();
    _backBox.DrawTexture();
    _slider.displayElements();
    _fullscreenBtn.Draw();
    _showFPS.Draw();
    _muteCheck.Draw();
    _title.TextDraw();
}
