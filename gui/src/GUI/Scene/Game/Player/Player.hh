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
               orientation facingDirection, std::size_t level, std::string team,
               std::shared_ptr<Raylib::Model3D> model);
        ~Player();

        std::size_t getId() const;
        std::size_t getLevel() const;
        std::string getTeam() const;
        Vector2 getPosition() const;
        std::vector<std::size_t> getInventory() const;
        orientation getOrientation() const;

        void setPosition(std::size_t x, std::size_t y, orientation orientation);
        void setInventory(std::vector<std::size_t> inventory);
        void setLevel(std::size_t level);
        void setIncantationStatus(playerStatus status);

        void broadcast(const std::string &message);
        void draw(const Vector2 &mapSize);
        bool hit(Ray mouseRay, const Vector2 &mapSize);
    private:
        std::size_t _id;
        Vector2 _position;
        orientation _orientation;
        std::size_t _level;
        std::string _team;
        std::vector<std::size_t> _inventory;
        std::shared_ptr<Raylib::Model3D> _model;
        playerStatus _status;
        BoundingBox _box;
    };
}
