/*
** EPITECH PROJECT, 2024
** Event.cpp
** File description:
** Event
*/

#include "Event.hh"

extern "C" {
    Vector2 Raylib::Event::myGetMousePosition()
    {
        return GetMousePosition();
    }

    bool Raylib::Event::myCheckCollisionPointRec(Vector2 point, Raylib::RectangleEnc rec)
    {
        return CheckCollisionPointRec(point, rec.getRectangle());
    }

    bool Raylib::Event::myIsMouseButtonDown(int button)
    {
        return IsMouseButtonDown(button);
    }

    bool Raylib::Event::myIsMouseButtonReleased(int button)
    {
        return IsMouseButtonReleased(button);
    }

    bool Raylib::Event::myIsKeyPressed(int key)
    {
        return IsKeyPressed(key);
    }

    bool Raylib::Event::myIsKeyReleased(int key)
    {
        return IsKeyPressed(key);
    }

    bool Raylib::Event::myIsKeyDown(int key)
    {
        return IsKeyPressed(key);
    }
}
