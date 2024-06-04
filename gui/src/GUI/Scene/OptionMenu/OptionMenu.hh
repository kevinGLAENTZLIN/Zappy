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
        // TODO: put all the elements of the option menu here
    };
}
