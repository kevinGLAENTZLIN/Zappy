/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** CommonElements
*/

#include "CommonElements.hh"
#include <map>

Zappy::CommonElements::CommonElements():
    _currentScene(0), _camera(), _socket(0), _musicVolume(0.5), _soundVolume(0.5)
{
}

Zappy::CommonElements::~CommonElements()
{
}

void Zappy::CommonElements::setCurrentScene(const std::size_t &scene)
{
    _currentScene = scene;
}

void Zappy::CommonElements::setCamera(const Raylib::Camera &camera)
{
    _camera = camera;
}

void Zappy::CommonElements::setSocket(const std::size_t &socket)
{
    _socket = socket;
}

void Zappy::CommonElements::setMusicVolume(const double &volume)
{
    _musicVolume = volume;
}

void Zappy::CommonElements::setSoundVolume(const double &volume)
{
    _soundVolume = volume;
}

std::size_t Zappy::CommonElements::getCurrentScene() const
{
    return _currentScene;
}

Raylib::Camera Zappy::CommonElements::getCamera() const
{
    return _camera;
}

std::size_t Zappy::CommonElements::getSocket() const
{
    return _socket;
}

double Zappy::CommonElements::getMusicVolume() const
{
    return _musicVolume;
}

double Zappy::CommonElements::getSoundVolume() const
{
    return _soundVolume;
}
