/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#include "Player.hh"
#include <raylib.h>

Zappy::Player::Player(std::size_t id, std::size_t posX, std::size_t posY,
                      std::size_t facingDirection, std::size_t level,
                      std::string team, std::shared_ptr<Raylib::Model3D> models):
    _id(id), _position({static_cast<float>(posX), static_cast<float>(posY)}),
    _orientation(facingDirection), _level(level), _team(team), _model(models),
    _orientationMultiplicator(4), _broadCastRadius(0), _isBroadcasting(false),
    _status(WANDERING)
{
    _3DPosition = {0, 0, 0};
    _box = _model->getModelBoundingBox();
    _orientationMultiplicator[DOWN_ORIENTATION] = 0;
    _orientationMultiplicator[RIGHT_ORIENTATION] = 1;
    _orientationMultiplicator[UP_ORIENTATION] = 2;
    _orientationMultiplicator[LEFT_ORIENTATION] = 3;
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

std::size_t Zappy::Player::getOrientation() const
{
    return _orientation;
}

void Zappy::Player::setPosition(std::size_t x, std::size_t y, std::size_t orientation,
                                Vector2 mapSize)
{
    _position = {static_cast<float>(x), static_cast<float>(y)};
    _3DPosition = {static_cast<float>(x - mapSize.x / 2 + 0.5), 0,
                   static_cast<float>(y - mapSize.y / 2 + 0.5)};
    _orientation = orientation - 1;
    _isBroadcasting = false;
}

void Zappy::Player::setInventory(std::vector<std::size_t> inventory)
{
    _inventory = inventory;
}

void Zappy::Player::setLevel(std::size_t level)
{
    _level = level;
}

void Zappy::Player::setStatus(playerStatus status)
{
    _status = status;
}

void Zappy::Player::broadcast(const std::string &message)
{
    (void)message;
    _isBroadcasting = true;
}

void Zappy::Player::draw()
{
    if (_model == nullptr || (_3DPosition.x == 0 && _3DPosition.z == 0))
        return;
    _model->setPosition(_3DPosition.x, _3DPosition.y, _3DPosition.z);
    switch (_status) {
        case WANDERING:
            _model->setRotation(static_cast<int>(_orientationMultiplicator[_orientation]) * 90);
            break;
        case INCANTATING:
            _model->setRotation(_model->getRotation() + 10);
            break;
        default:
            break;
    }
    if (_isBroadcasting == true) {
        DrawCircle3D({_3DPosition.x, 0.5, _3DPosition.z}, _broadCastRadius,
                     {1, 0, 0} , 90, RAYWHITE);
        if (_broadCastRadius > 42) {
            _isBroadcasting = false;
            _broadCastRadius = 0;
        } else
            _broadCastRadius += 0.2;
    }
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
