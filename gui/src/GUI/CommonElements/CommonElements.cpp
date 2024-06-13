/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** CommonElements
*/

#include "CommonElements.hh"
#include <map>

Zappy::CommonElements::CommonElements():
    _currentScene(0), _oldScene(0), _camera(), _socket(0), _soundVolume(0.5), _music("gui/assets/audio/menu.mp3"), _mute(false), _showFPS(false)
{
}

Zappy::CommonElements::~CommonElements()
{
}

void Zappy::CommonElements::setCurrentScene(const std::size_t &scene)
{
    _currentScene = scene;
}

void Zappy::CommonElements::setOldScene(const std::size_t &scene)
{
    _oldScene = scene;
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
    _music.setVolume(volume);
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

void Zappy::CommonElements::setMute()
{
    _mute = !_mute;
}

void Zappy::CommonElements::setShowFPS(const bool &value)
{
    _showFPS = value;
}

void Zappy::CommonElements::drawFPS()
{
    if (_showFPS)
        DrawFPS(5, 5);
}

std::size_t Zappy::CommonElements::getCurrentScene() const
{
    return _currentScene;
}

std::size_t Zappy::CommonElements::getOldScene() const
{
    return _oldScene;
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
    return _music.getVolume();
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

bool Zappy::CommonElements::getMute() const
{
    return _mute;
}

bool Zappy::CommonElements::getShowFPS() const
{
    return _showFPS;
}