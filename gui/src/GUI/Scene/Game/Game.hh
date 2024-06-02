/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Game
*/


#pragma once

#include <iostream>
#include <memory>

#include "../IScene.hh"
#include "../../CommonElements/CommonElements.hh"

namespace Zappy {
    class Game : public IScene {
    public:
        Game(std::shared_ptr<CommonElements> commonElements);
        ~Game() override;
        void computeLogic() override;
        void displayElements(void) override;
    private:
        std::shared_ptr<CommonElements> _commonElements;
        // TODO: put all the elements of the main menu here
    };
}
