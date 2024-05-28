/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Rectangle
*/

#include "Rectangle.hh"
#include "Screen.hh"

Raylib::Rectangle::Rectangle(double x, double y, double width, double height, Color color = WHITE):
    _x(Screen::myGetScreenWidth() * (x / 100) - width / 2),
    _y(Screen::myGetScreenHeight() * (y / 100) - height / 2),
    _width(Screen::myGetScreenWidth() * (width / 100)),
    _height(Screen::myGetScreenHeight() * (height / 100)), _color(color)
{
}

Raylib::Rectangle::~Rectangle()
{
}

std::pair<double, double> Raylib::Rectangle::getPosition() const
{
    return {_x, _y};
}

std::pair<double, double> Raylib::Rectangle::getSize() const
{
    return {_width, _height};
}

Color Raylib::Rectangle::getColor() const
{
    return _color;
}

extern "C" {
    void Raylib::Rectangle::myDrawRectangle() const
    {
        DrawRectangle(_x, _y, _width, _height, _color);
    }
}
