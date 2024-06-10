/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Model3D
*/


#pragma once

#include <raylib.h>
#include <iostream>

#include "../Texture/Texture.hh"

namespace Raylib {
    class Model3D {
    public:
        Model3D(const std::string &fileName, const std::string &texture,
                double posX = 0, double posY = 0, double posZ = 0, double roll = 0,
                double pitch = 0, double yaw = 0, double scale = 1);
        ~Model3D();

        void setPosition(double x, double y, double z);
        void setRotation(double roll, double pitch, double yaw);

        void ModelDraw();
    private:
        void createModel(const std::string &fileName);
        void destroyModel();
        Model _model;
        Texture _texture;
        double _scale;

        Vector3 _position;
        Vector3 _rotation;
        BoundingBox _boundingBox;
    };
}
