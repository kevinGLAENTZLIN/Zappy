/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Camera
*/

#include "Camera.hh"

#include <iostream>

Raylib::Camera::Camera()
{
    setupCamera();
}

Raylib::Camera::~Camera()
{}

extern "C" {
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
        _camera.position = { 0.0f, 10.0f, 10.0f };
        _camera.target = { 0.0f, 0.0f, 0.0f };
        _camera.up = { 0.0f, 1.0f, 0.0f };
        _camera.fovy = 45.0f;
        _camera.projection = CAMERA_PERSPECTIVE;
        UpdateCamera(&_camera, CAMERA_THIRD_PERSON);
    }
}
