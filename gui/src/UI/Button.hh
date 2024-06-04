/*
** EPITECH PROJECT, 2024
** ZAppy
** File description:
** Button.hh
*/

#pragma once
#include "../Raylib/Raylib.hh"
#include <iostream>
#include <utility>
#include <memory>

namespace Zappy {
    class Button {
        public:
            Button(const std::size_t &posX, const std::size_t &posY, const std::string &assetPath,
                   const std::string &text, const std::string &font);
            ~Button();
            bool IsButtonPressed();
            void Draw();
            void Event();

        protected:
        private:
            bool _btnAction;
            std::unique_ptr<Raylib::Text> _text;
            Raylib::SpriteSheet _btnTexture;
            Raylib::RectangleEnc _btnBounds;
    };
}
