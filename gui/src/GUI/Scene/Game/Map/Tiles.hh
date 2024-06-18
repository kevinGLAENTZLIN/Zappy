/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tiles
*/


#pragma once

#include "../../../../Raylib/3DEnvironment/Model3D.hh"
#include "../Elements.hh"

#include <vector>
#include <memory>

namespace Zappy {

    enum color {
        LIGHT_GREEN = 0,
        DARK_GREEN = 1,
    };

    class Tiles {
    public:
        Tiles(int x, int y, Vector2 mapSize,
              std::vector<std::shared_ptr<Raylib::Model3D>> models);
        ~Tiles();

        void setResources(std::vector<std::size_t> resourcesQuantity);

        Vector2 getIndex() const;
        std::vector<std::size_t> getResources() const;

        bool Hits(Ray mouseRay);
        void Draw();
    private:
        Vector2 _index;
        Vector2 _mapSize;
        Vector3 _3DPosition;
        BoundingBox _bounds;
        std::vector<std::shared_ptr<Raylib::Model3D>> _models;
        std::vector<std::size_t> _resourcesQuantity;
        color _color;
    };
}
