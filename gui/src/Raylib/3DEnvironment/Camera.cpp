/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Camera
*/

#include "Camera.hh"

#include <iostream>
#include <raylib.h>

Raylib::Camera::Camera()
{
    setupCamera();
}

Raylib::Camera::~Camera()
{}

Camera3D Raylib::Camera::getCamera()
{
    return _camera;
}

extern "C" {
    void Raylib::Camera::cameraUpdate(std::size_t flags)
    {
        UpdateCamera(&_camera, flags);
    }

    void Raylib::Camera::begin3DMode()
    {
        BeginMode3D(_camera);
    }

    void Raylib::Camera::end3DMode()
    {
        EndMode3D();
    }

    void Raylib::Camera::setupCamera()
    {
        // INFO: those variable are not defintive and will be changed
        _camera.position = { 0.0f, 42.0f, 42.0f };
        _camera.target = { 0.0f, 0.0f, 0.0f };
        _camera.up = { 0.0f, 1.0f, 0.0f };
        _camera.fovy = 45.0f;
        _camera.projection = CAMERA_PERSPECTIVE;
        UpdateCamera(&_camera, CAMERA_ORBITAL);
    }
}
