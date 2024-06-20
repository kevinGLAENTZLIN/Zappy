/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/


#pragma once

#include <iostream>
#include <raylib.h>
#include <vector>
#include <memory>

#include "../../../../Raylib/3DEnvironment/Model3D.hh"
#include "../Elements.hh"

namespace Zappy {
    class Player {
    public:
        Player(std::size_t id, std::size_t posX, std::size_t posY,
               std::size_t facingDirection, std::size_t level, std::string team,
               std::shared_ptr<Raylib::Model3D> model);
        ~Player();

        std::size_t getId() const;
        std::size_t getLevel() const;
        std::string getTeam() const;
        Vector2 getPosition() const;
        Vector3 get3DPosition() const;
        std::vector<std::size_t> getInventory() const;
        std::size_t getOrientation() const;

        void setPosition(std::size_t x, std::size_t y, std::size_t orientation,
                         Vector2 mapSize);
        void setInventory(std::vector<std::size_t> inventory);
        void setLevel(std::size_t level);
        void setStatus(playerStatus status);

        void broadcast(const std::string &message);
        void draw();
        bool hit(Ray mouseRay);
    private:
        std::size_t _id;
        Vector2 _position;
        Vector3 _3DPosition;
        std::size_t _orientation;
        std::size_t _level;
        std::string _team;
        std::vector<std::size_t> _inventory;
        std::shared_ptr<Raylib::Model3D> _model;
        std::vector<std::size_t> _orientationMultiplicator;
        double _broadCastRadius;
        bool _isBroadcasting;
        playerStatus _status;
        BoundingBox _box;
    };
}
