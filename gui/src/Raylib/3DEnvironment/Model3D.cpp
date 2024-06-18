/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Model3D
*/

#include "Model3D.hh"
#include <raylib.h>
#include <raymath.h>

Raylib::Model3D::Model3D(const std::string &fileName, const std::string &texture,
                         double posX, double posY, double posZ, double roll,
                         double pitch, double yaw, double scale):
    _texture(texture)
{
    _position = {static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(posZ)};
    _rotation = {static_cast<float>(roll), static_cast<float>(pitch), static_cast<float>(yaw)};
    createModel(fileName);
    scaleModel(scale);
}

Raylib::Model3D::~Model3D()
{
    destroyModel();
}

void Raylib::Model3D::setPosition(double x, double y, double z)
{
    _position = {static_cast<float>(x), static_cast<float>(y),
        static_cast<float>(z)};
}

void Raylib::Model3D::setRotation(double roll, double pitch, double yaw)
{
    _rotation = {static_cast<float>(roll), static_cast<float>(pitch),
        static_cast<float>(yaw)};
}

extern "C" {
    BoundingBox Raylib::Model3D::getModelBoundingBox() const
    {
        return GetModelBoundingBox(_model);
    }

    void Raylib::Model3D::ModelDraw() const
    {
        DrawModelEx(_model, _position, _rotation, 0, {1, 1, 1}, WHITE);
    }

    void Raylib::Model3D::createModel(const std::string &fileName)
    {
        _model = LoadModel(fileName.c_str());
        _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture.GetTexture();
    }

    void Raylib::Model3D::destroyModel()
    {
        UnloadModel(_model);
    }

    void Raylib::Model3D::scaleModel(double scale)
    {
        Matrix scaleMatrix = MatrixScale(scale, scale, scale);
        _model.transform = MatrixMultiply(_model.transform, scaleMatrix);
    }
}
