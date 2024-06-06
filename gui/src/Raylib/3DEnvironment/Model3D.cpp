/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Model3D
*/

#include "Model3D.hh"

Raylib::Model3D::Model3D(const std::string &fileName, const std::string &texture,
                         double posX, double posY, double posZ, double roll,
                         double pitch, double yaw, double scale):
    _texture(texture), _scale(scale)
{
    std::cout << "Model3D constructor" << std::endl;
    _position = {static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(posZ)};
    _rotation = {static_cast<float>(roll), static_cast<float>(pitch), static_cast<float>(yaw)};
    createModel(fileName);
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
    void Raylib::Model3D::ModelDraw()
    {
        DrawModel(_model, _position, _scale, WHITE);
    }

    void Raylib::Model3D::createModel(const std::string &fileName)
    {
        _model = LoadModel(fileName.c_str());
        _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture.GetTexture();
        _boundingBox = GetModelBoundingBox(_model);
    }

    void Raylib::Model3D::destroyModel()
    {
        UnloadModel(_model);
    }
}
