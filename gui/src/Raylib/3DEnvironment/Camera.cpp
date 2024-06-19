/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Camera
*/

#include "Camera.hh"

#include <iostream>
#include <raylib.h>
#include <raymath.h>

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

void Raylib::Camera::setCameraTarget(Vector3 focus)
{
    _camera.position.x -= _camera.target.x;
    _camera.position.y -= _camera.target.y;
    _camera.position.z -= _camera.target.z;
    _camera.target = focus;
    _camera.position.x += _camera.target.x;
    _camera.position.y += _camera.target.y;
    _camera.position.z += _camera.target.z;
}

void Raylib::Camera::setCameraDistanceToFocus(float distance)
{
    _camera.position.z += distance;
    _camera.position.y += distance;
    if (_camera.position.z - _camera.target.z < 5.0f) {
        _camera.position.z = 5.0f + _camera.target.z;
        _camera.position.y = 5.0f + _camera.target.y;
    }
    if (_camera.position.z - _camera.target.z > 100.0f) {
        _camera.position.z = 100.0f + _camera.target.z;
        _camera.position.y = 100.0f + _camera.target.y;
    }
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
