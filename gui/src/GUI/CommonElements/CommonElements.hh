/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** CommonElements
*/


#pragma once

#include <iostream>

#include "../../Raylib/3DEnvironment/Camera.hh"

namespace Zappy {
    class CommonElements {
    public:
        CommonElements();
        ~CommonElements();

        void setCurrentScene(const std::size_t &scene);
        void setCamera(const Raylib::Camera &camera);
        void setSocket(const std::size_t &socket);
        void setMusicVolume(const double &volume);
        void setSoundVolume(const double &volume);

        std::size_t getCurrentScene() const;
        Raylib::Camera getCamera() const;
        std::size_t getSocket() const;
        double getMusicVolume() const;
        double getSoundVolume() const;
    private:
        std::size_t _currentScene;
        Raylib::Camera _camera;
        std::size_t _socket;
        double _musicVolume;
        double _soundVolume;
    };
}
