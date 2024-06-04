/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** CommonElements
*/


#pragma once

#include <iostream>

#include "../../Raylib/Raylib.hh"

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
        void setPort(const std::size_t &port);
        void setIp(const std::string &ip);
        void setConnect(const bool &connected);

        std::size_t getCurrentScene() const;
        Raylib::Camera getCamera() const;
        std::size_t getSocket() const;
        double getMusicVolume() const;
        double getSoundVolume() const;
        std::size_t getPort() const;
        std::string getIp() const;
        bool getConnect() const;
        Raylib::MusicEnc getMusic() const;
    private:
        std::size_t _currentScene;
        Raylib::Camera _camera;
        std::size_t _socket;
        double _musicVolume;
        double _soundVolume;
        Raylib::MusicEnc _music;
        std::size_t _port;
        std::string _ip;
        bool _connected;
    };
}
