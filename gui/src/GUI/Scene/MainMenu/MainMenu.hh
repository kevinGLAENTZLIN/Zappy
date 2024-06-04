/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** MainMenu
*/


#pragma once

#include <iostream>
#include <memory>

#include "../IScene.hh"
#include "../../CommonElements/CommonElements.hh"
#include "../../../UI/Button.hh"
#include "../../../Utils/GuiSocket.hh"

namespace Zappy {
    class MainMenu : public IScene {
    public:
        MainMenu(std::shared_ptr<CommonElements> commonElements);
        ~MainMenu() override;
        void computeLogic() override;
        void displayElements(void) override;
    private:
        std::shared_ptr<CommonElements> _commonElements;
        Button _playBtn;
        Button _optionBtn;
        Button _quitBtn;
        GuiSocket _guiSock;
        // Raylib::Texture _texture;
    };
}
