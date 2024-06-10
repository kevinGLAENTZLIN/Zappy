/*
** EPITECH PROJECT, 2024
** Slider.hh
** File description:
** Slider
*/

#pragma once
#include "../Raylib/Raylib.hh"

namespace Zappy {
    class Slider {
        public:
            Slider(const std::string &title, float posX, float posY, float value = 0.5);
            ~Slider();
            void computeLogic();
            void displayElements();
            bool isCursorPressed();
            float getValue() const;

        protected:
        private:
            std::size_t _size;
            Raylib::Texture _barTexture;
            Raylib::Text _title;
            Raylib::Texture _cursorTexture;
            Raylib::RectangleEnc _cursorRec;
            Raylib::RectangleEnc _barRec;
            bool _cursorAction;
            float _sliderValue;
    };
}
