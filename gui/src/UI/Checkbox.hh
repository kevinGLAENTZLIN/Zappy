/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Checkbox
*/

#pragma once
#include "../Raylib/Raylib.hh"

namespace Zappy {
    class Checkbox {
        public:
            Checkbox(double posX, double posY, const std::string &title, Color textColor);
            ~Checkbox();
            void Event();
            bool isChecked() const;
            void Draw();

        protected:
        private:
            Raylib::Texture _checkbox;
            Raylib::Texture _check;
            Raylib::RectangleEnc _checkRec;
            Raylib::Text _title;
            bool _checked;
    };
}
