/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Camera
*/


#pragma once

#include <raylib.h>
#include <iostream>

namespace Raylib {
    class Camera {
    public:
        Camera();
        ~Camera();

        Camera3D getCamera();

        void begin3DMode();
        void end3DMode();
        void cameraUpdate(std::size_t flags);
    private:
        void setupCamera();
        Camera3D _camera;
        NPatchInfo _jaj;
    };
}
