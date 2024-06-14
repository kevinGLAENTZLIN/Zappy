/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tiles
*/

#include "Tiles.hh"
#include <raylib.h>

Zappy::Tiles::Tiles(int x, int y, Vector2 mapSize,
                    std::vector<std::shared_ptr<Raylib::Model3D>> models):
    _index({static_cast<float>(x), static_cast<float>(y)}),
    _mapSize(mapSize), _models(models)
{
    _bounds = (BoundingBox){(Vector3){_index.x - _mapSize.x / 2, 0,
                                      _index.y - _mapSize.y / 2},
                            (Vector3){_index.x - _mapSize.x / 2 + 1.f, 0,
                                      _index.y - _mapSize.y / 2 + 1.f}};
}

Zappy::Tiles::~Tiles()
{
}

void Zappy::Tiles::setResources(std::vector<std::size_t> resourcesQuantity)
{
    _resourcesQuantity.clear();
    _resourcesQuantity = resourcesQuantity;
}

Vector2 Zappy::Tiles::getIndex() const
{
    return _index;
}

std::vector<std::size_t> Zappy::Tiles::getResources() const
{
    return _resourcesQuantity;
}

bool Zappy::Tiles::Hits(Ray mouseRay)
{
    return GetRayCollisionBox(mouseRay, _bounds).hit;
}

void Zappy::Tiles::Draw()
{
    Vector3 position = {_index.x - _mapSize.x / 2 + 0.5f, 0,
                        _index.y - _mapSize.y / 2 + 0.5f};
    Color color = {0, 255, 0, 255};

    if (static_cast<int>(_index.x + _index.y) % 2 == 0)
        color = {0, 155, 0, 255};
    DrawPlane(position, {1.0, 1.0}, color);
    for (std::size_t i = 0; i < _resourcesQuantity.size(); i++) {
        if (_resourcesQuantity[i] != 0 && i < _models.size() && _models[i] != nullptr) {
            switch(i) {
                case FOOD:
                    _models[i]->setPosition(_index.x - _mapSize.x / 2 + 0.5, 0,
                                            _index.y - _mapSize.y / 2 + 0.5);
                    break;
                case LINEMATE:
                    _models[i]->setPosition(_index.x - _mapSize.x / 2 + 0.1, 0,
                                            _index.y - _mapSize.y / 2 + 0.1);
                    break;
                case DERAUMERE:
                    _models[i]->setPosition(_index.x - _mapSize.x / 2 + 0.9, 0,
                                            _index.y - _mapSize.y / 2 + 0.1);
                    break;
                case SIBUR:
                    _models[i]->setPosition(_index.x - _mapSize.x / 2 + 0.1, 0,
                                            _index.y - _mapSize.y / 2 + 0.9);
                    break;
                case MENDIANE:
                    _models[i]->setPosition(_index.x - _mapSize.x / 2 + 0.9, 0,
                                            _index.y - _mapSize.y / 2 + 0.9);
                    break;
            }
            _models[i]->ModelDraw();
        }
    }
}
