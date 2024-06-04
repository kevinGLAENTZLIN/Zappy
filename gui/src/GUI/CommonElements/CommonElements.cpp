/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** CommonElements
*/

#include "CommonElements.hh"
#include <map>

Zappy::CommonElements::CommonElements():
    _currentScene(0), _camera(), _socket(0), _musicVolume(0.5), _soundVolume(0.5), _music("gui/assets/audio/menu.mp3")
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

void Zappy::CommonElements::setPort(const std::size_t &port)
{
    _port = port;
}

void Zappy::CommonElements::setIp(const std::string &ip)
{
    _ip = ip;
}

void Zappy::CommonElements::setConnect(const bool &connected)
{
    _connected = connected;
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

std::size_t Zappy::CommonElements::getPort() const
{
    return _port;
}

std::string Zappy::CommonElements::getIp() const
{
    return _ip;
}

bool Zappy::CommonElements::getConnect() const
{
    return _connected;
}

Raylib::MusicEnc Zappy::CommonElements::getMusic() const
{
    return _music;
}
