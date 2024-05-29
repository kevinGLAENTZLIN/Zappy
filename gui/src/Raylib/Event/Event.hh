/*
** EPITECH PROJECT, 2024
** Event.hh
** File description:
** Event
*/

#pragma once
#include <iostream>
#include "../Shapes/RectangleEnc.hh"

namespace Zappy {
    class Event {
        public:
            static Vector2 myGetMousePosition();
            static bool myCheckCollisionPointRec(Vector2 point, Raylib::RectangleEnc rec);
            static bool myIsMouseButtonDown(int button);
            static bool myIsMouseButtonReleased(int button);
            static bool myIsKeyPressed(int key);
            static bool myIsKeyReleased(int key);
            static bool myIsKeyDown(int key);
    };
}
