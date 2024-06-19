/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** GameInfo
*/


#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "../../../../Raylib/Raylib.hh"

#define OFFSET 0.0666f
#define HEIGHT GetTexture().height
#define WIDTH GetTexture().width

namespace Zappy {
    class GameInfo {
    public:
        GameInfo();
        ~GameInfo();

        void updateTitle(std::size_t nbPlayers);
        void updateValues(std::vector<std::size_t> values);

        void display();
    private:
        void setUpTexts();

        double _scale;
        Raylib::Texture _background;
        std::shared_ptr<Raylib::Text> _title;
        std::vector<std::shared_ptr<Raylib::Text>> _values;
    };
}
