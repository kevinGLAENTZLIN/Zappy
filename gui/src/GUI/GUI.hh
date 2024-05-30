/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** GUI
*/


#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "CommonElements/CommonElements.hh"
#include "../Raylib/Window/Window.hh"
#include "Scene/IScene.hh"
#include "Scene/SceneFactory.hh"

namespace Zappy {
    class GUI {
    public:
        GUI(const std::vector<std::string> &args);
        ~GUI();
    private:
        void handleArguments(const std::vector<std::string> &args);
        void runGUI();
        void initScenes();

        std::shared_ptr<CommonElements> _commonElements;
        std::unique_ptr<Raylib::Window> _window;
        std::vector<std::unique_ptr<IScene>> _scenes;
        std::size_t _port;
        std::string _ip;
    };
}
