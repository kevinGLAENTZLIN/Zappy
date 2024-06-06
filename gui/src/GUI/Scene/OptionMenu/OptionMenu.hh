/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** OptionMenu
*/

#pragma once

#include <iostream>
#include <memory>

#include "../IScene.hh"
#include "../../CommonElements/CommonElements.hh"
#include "../../../UI/Button.hh"
#include "../../../UI/Checkbox.hh"
#include "../../../UI/Slider.hh"
#include "../../../Raylib/Raylib.hh"

namespace Zappy {
    class OptionMenu : public IScene {
    public:
        OptionMenu(std::shared_ptr<CommonElements> commonElements);
        ~OptionMenu() override;
        void computeLogic() override;
        void displayElements(void) override;
    private:
        std::shared_ptr<CommonElements> _commonElements;
        Button _backBtn;
        Raylib::Texture _backBox;
        Slider _slider;
        Button _fullscreenBtn;
        Checkbox _showFPS;
        Checkbox _muteCheck;
        Raylib::Text _title;
    };
}
