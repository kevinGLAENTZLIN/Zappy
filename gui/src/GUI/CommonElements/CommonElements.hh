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
        void setOldScene(const std::size_t &scene);
        void setCamera(const Raylib::Camera &camera);
        void setSocket(const std::size_t &socket);
        void setMusicVolume(const double &volume);
        void setSoundVolume(const double &volume);
        void setPort(const std::size_t &port);
        void setIp(const std::string &ip);
        void setConnect(const bool &connected);
        void setMute();
        void setShowFPS(const bool &value);
        void setExit(bool value);

        void drawFPS();

        std::size_t getCurrentScene() const;
        std::size_t getOldScene() const;
        Raylib::Camera getCamera() const;
        std::size_t getSocket() const;
        double getMusicVolume() const;
        double getSoundVolume() const;
        std::size_t getPort() const;
        std::string getIp() const;
        bool getConnect() const;
        bool getMute() const;
        Raylib::MusicEnc getMusic() const;
        bool getShowFPS() const;
        bool getExit() const;
    private:
        std::size_t _currentScene;
        std::size_t _oldScene;
        Raylib::Camera _camera;
        std::size_t _socket;
        double _soundVolume;
        Raylib::MusicEnc _music;
        std::size_t _port;
        std::string _ip;
        bool _connected;
        bool _mute;
        bool _showFPS;
        bool _exit;
    };
}
