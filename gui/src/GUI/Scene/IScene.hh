/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IScene
*/


#pragma once

#include <iostream>

namespace Zappy {
    class IScene {
    public:
        virtual ~IScene() = default;
        virtual void computeLogic() = 0;
        virtual void displayElements(void) = 0;
    };
}
