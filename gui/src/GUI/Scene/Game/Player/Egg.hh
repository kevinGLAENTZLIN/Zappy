/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/


#pragma once

#include <iostream>
#include <memory>

#include "../../../../Raylib/Raylib.hh"

namespace Zappy {
    class Egg {
    public:
        Egg(std::size_t id, std::size_t x, std::size_t y,
            std::shared_ptr<Raylib::Model3D> model);
        ~Egg();

        Vector2 getPosition() const;
        std::size_t getId() const;

        void Draw(Vector2 mapSize);
    private:
        std::size_t _id;
        Vector2 _position;
        std::shared_ptr<Raylib::Model3D> _model;
    };
}
