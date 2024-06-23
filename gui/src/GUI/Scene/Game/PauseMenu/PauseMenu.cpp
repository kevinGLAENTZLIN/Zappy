/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** PauseMenu
*/

#include "PauseMenu.hh"

Zappy::PauseMenu::PauseMenu(std::shared_ptr<CommonElements> commonElements):
    _visible(false), _box("gui/assets/box.png", 50, 55, 0, 0.15),
    _text("Pause Menu", 70, "gui/assets/Futura Condensed Medium.ttf", _box.getPercentPos().first,
        _box.getPercentPos().second - 30, 2, WHITE, Raylib::PERCENT),
    _resumeBtn(_box.getPercentPos().first, _box.getPercentPos().second - 13, "gui/assets/ButtonLight.png", "RESUME", "gui/assets/Futura Condensed Medium.ttf", WHITE),
    _optionsBtn(_box.getPercentPos().first, _box.getPercentPos().second + 5, "gui/assets/ButtonLight.png", "OPTIONS", "gui/assets/Futura Condensed Medium.ttf", WHITE),
    _quitBtn(_box.getPercentPos().first, _box.getPercentPos().second + 23, "gui/assets/ButtonLight.png", "MAIN MENU", "gui/assets/Futura Condensed Medium.ttf", WHITE),
    _commonElements(commonElements)
{
}

Zappy::PauseMenu::~PauseMenu()
{
}

bool Zappy::PauseMenu::isVisible() const
{
    return _visible;
}

void Zappy::PauseMenu::changeVisibility()
{
    _visible = !_visible;
}

void Zappy::PauseMenu::computeLogic(Vector2 mapSize)
{
    Raylib::Camera camera = _commonElements->getCamera();
    std::size_t distance = mapSize.x > mapSize.y ? mapSize.x : mapSize.y;
    _resumeBtn.Event();
    _optionsBtn.Event();
    _quitBtn.Event();
    if (_resumeBtn.IsButtonPressed())
        _visible = false;
    if (_optionsBtn.IsButtonPressed()) {
        camera.setCameraTarget({0, 0, 0});
        camera.setCameraDistanceToFocusHard(distance);
        _commonElements->setCamera(camera);
        _commonElements->setCurrentScene(1);
        _commonElements->setOldScene(2);
    }
    if (_quitBtn.IsButtonPressed()) {
        camera.setCameraTarget({0, 0, 0});
        _commonElements->setCamera(camera);
        _commonElements->setCurrentScene(0);
        _visible = false;
    }
}

void Zappy::PauseMenu::Draw()
{
    _box.DrawTexture();
    _text.TextDraw();
    _resumeBtn.Draw();
    _optionsBtn.Draw();
    _quitBtn.Draw();
}
