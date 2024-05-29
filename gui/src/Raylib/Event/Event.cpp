/*
** EPITECH PROJECT, 2024
** Event.cpp
** File description:
** Event
*/

#include "Event.hh"

Vector2 myGetMousePosition()
{
    return GetMousePosition();
}

bool Zappy::Event::myCheckCollisionPointRec(Vector2 point, Raylib::RectangleEnc rec)
{
    return CheckCollisionPointRec(point, rec.getRectangle());
}

bool Zappy::Event::myIsMouseButtonDown(int button)
{
    return IsMouseButtonDown(button);
}

bool Zappy::Event::myIsMouseButtonReleased(int button)
{
    return IsMouseButtonReleased(button);
}

bool Zappy::Event::myIsKeyPressed(int key)
{
    return IsKeyPressed(key);
}

bool Zappy::Event::myIsKeyReleased(int key)
{
    return IsKeyPressed(key);
}

bool Zappy::Event::myIsKeyDown(int key)
{
    return IsKeyPressed(key);
}
