/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#include "Player.hh"
#include <raylib.h>

Zappy::Player::Player(std::size_t id, std::size_t posX, std::size_t posY,
                      orientation facingDirection, std::size_t level,
                      std::string team, std::shared_ptr<Raylib::Model3D> models):
    _id(id), _position({static_cast<float>(posX), static_cast<float>(posY)}),
    _orientation(facingDirection), _level(level), _team(team), _model(models),
    _status(WANDERING)
{}

Zappy::Player::~Player()
{
}

std::size_t Zappy::Player::getId() const
{
    return _id;
}

std::size_t Zappy::Player::getLevel() const
{
    return _level;
}

std::string Zappy::Player::getTeam() const
{
    return _team;
}

Vector2 Zappy::Player::getPosition() const
{
    return _position;
}

std::vector<std::size_t> Zappy::Player::getInventory() const
{
    return _inventory;
}

Zappy::orientation Zappy::Player::getOrientation() const
{
    return _orientation;
}

void Zappy::Player::setPosition(std::size_t x, std::size_t y, orientation orientation)
{
    _position = {static_cast<float>(x), static_cast<float>(y)};
    _orientation = orientation;
}

void Zappy::Player::setInventory(std::vector<std::size_t> inventory)
{
    _inventory = inventory;
}

void Zappy::Player::setLevel(std::size_t level)
{
    _level = level;
}

void Zappy::Player::setIncantationStatus(playerStatus status)
{
    _status = status;
}

void Zappy::Player::broadcast(const std::string &message)
{
    std::cout << message << std::endl;
}

void Zappy::Player::draw(const Vector2 &mapSize)
{
    _model->setPosition(_position.x - mapSize.x / 2 + 0.5, 0,
                        _position.y - mapSize.y / 2 + 0.5);
    _model->setRotation(0, 90 * static_cast<int>(_orientation), 0);
    _model->ModelDraw();
}
