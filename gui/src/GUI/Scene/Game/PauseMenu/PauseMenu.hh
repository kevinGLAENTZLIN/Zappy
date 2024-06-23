/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Pause Menu
*/

#pragma once
#include "../../../../Raylib/Raylib.hh"
#include "../../../../UI/Button.hh"
#include "../../../CommonElements/CommonElements.hh"

namespace Zappy {
    class PauseMenu {
        public:
            PauseMenu(std::shared_ptr<CommonElements> commonElements);
            ~PauseMenu();
            bool isVisible() const;
            void changeVisibility();
            void computeLogic(Vector2 mapSize);
            void Draw();

        protected:
        private:
            bool _visible;
            Raylib::Texture _box;
            Raylib::Text _text;
            Button _resumeBtn;
            Button _optionsBtn;
            Button _quitBtn;
            std::shared_ptr<CommonElements> _commonElements;
    };
}
