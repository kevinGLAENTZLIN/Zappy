/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** RectangleEnc
*/

#include "RectangleEnc.hh"
#include "../Screen/Screen.hh"
#include <iostream>

Raylib::RectangleEnc::RectangleEnc():
    _x(0), _y(0), _width(0), _height(0), _color(WHITE)
{}

Raylib::RectangleEnc::RectangleEnc(double x, double y, double width, double height, Color color = WHITE):
    _x(Screen::myGetScreenWidth() * (x / 100) - width / 2),
    _y(Screen::myGetScreenHeight() * (y / 100) - height / 2),
    _width(Screen::myGetScreenWidth() * (width / 100)),
    _height(Screen::myGetScreenHeight() * (height / 100)), _color(color)
{}

Raylib::RectangleEnc::~RectangleEnc()
{
}

std::pair<double, double> Raylib::RectangleEnc::getPosition() const
{
    return {_x, _y};
}

std::pair<double, double> Raylib::RectangleEnc::getSize() const
{
    return {_width, _height};
}

Color Raylib::RectangleEnc::getColor() const
{
    return _color;
}

Rectangle Raylib::RectangleEnc::getRectangle() const
{
    return {static_cast<float>(_x), static_cast<float>(_y),
            static_cast<float>(_width), static_cast<float>(_height)};
}

void Raylib::RectangleEnc::setPosition(double x, double y)
{
    _x = x;
    _y = y;
}

void Raylib::RectangleEnc::setSize(double width, double height)
{
    _width = width;
    _height = height;
}

extern "C" {
    void Raylib::RectangleEnc::myDrawRectangle() const
    {
        DrawRectangle(_x, _y, _width, _height, _color);
    }
}
