/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** SceneFactory
*/


#pragma once

#include <memory>

#include "IScene.hh"
#include "../CommonElements/CommonElements.hh"

namespace Zappy {
    class SceneFactory {
    public:
        static std::unique_ptr<IScene> createMainMenu(std::shared_ptr<CommonElements> commonElements);
        static std::unique_ptr<IScene> createOptionMenu(std::shared_ptr<CommonElements> commonElements);
        static std::unique_ptr<IScene> createGame(std::shared_ptr<CommonElements> commonElements);
    };
}
