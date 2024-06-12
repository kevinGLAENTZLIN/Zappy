/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#include "Egg.hh"

Zappy::Egg::Egg(std::size_t id, std::size_t x, std::size_t y,
                std::shared_ptr<Raylib::Model3D> model):
    _id(id), _position{static_cast<float>(x), static_cast<float>(y)}, _model(model)
{}

Zappy::Egg::~Egg()
{}

Vector2 Zappy::Egg::getPosition() const
{
    return _position;
}

std::size_t Zappy::Egg::getId() const
{
    return _id;
}

void Zappy::Egg::Draw(Vector2 mapSize)
{
    _model->setPosition(_position.x - mapSize.x / 2 + 0.5, 0,
                        _position.y - mapSize.y / 2 + 0.5);
    _model->ModelDraw();
}
