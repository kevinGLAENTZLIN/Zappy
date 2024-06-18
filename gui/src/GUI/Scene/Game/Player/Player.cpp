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
{
    _3DPosition = {0, 0, 0};
    _box = _model->getModelBoundingBox();
}

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

Vector3 Zappy::Player::get3DPosition() const
{
    return _3DPosition;
}

std::vector<std::size_t> Zappy::Player::getInventory() const
{
    return _inventory;
}

Zappy::orientation Zappy::Player::getOrientation() const
{
    return _orientation;
}

void Zappy::Player::setPosition(std::size_t x, std::size_t y, orientation orientation,
                                Vector2 mapSize)
{
    _position = {static_cast<float>(x), static_cast<float>(y)};
    _3DPosition = {static_cast<float>(x - mapSize.x / 2 + 0.5), 0,
                   static_cast<float>(y - mapSize.y / 2 + 0.5)};
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

void Zappy::Player::draw()
{
    if (_model == nullptr || (_3DPosition.x == 0 && _3DPosition.z == 0))
        return;
    _model->setPosition(_3DPosition.x, _3DPosition.y, _3DPosition.z);
    _model->setRotation(0, 90 * static_cast<int>(_orientation), 0);
    _model->ModelDraw();
}

bool Zappy::Player::hit(Ray mouseRay)
{
    BoundingBox box = _box;

    box.min.x += _3DPosition.x;
    box.min.z += _3DPosition.z;
    box.max.x += _3DPosition.x;
    box.max.z += _3DPosition.z;
    return GetRayCollisionBox(mouseRay, box).hit;
}
