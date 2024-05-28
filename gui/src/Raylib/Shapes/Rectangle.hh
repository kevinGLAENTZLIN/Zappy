/*
** EPITECH PROJECT, 2024
** Rectangle.hh
** File description:
** Rectangle
*/

#pragma once
#include <raylib.h>
#include <utility>

namespace Raylib {
    class Rectangle {
        public:
            Rectangle(double x, double y, double width, double height, Color color);
            ~Rectangle();
            std::pair<double, double> getPosition() const;
            std::pair<double, double> getSize() const;
            Color getColor() const;
            void myDrawRectangle() const;

        protected:
        private:
            double _x;
            double _y;
            double _width;
            double _height;
            Color _color;
    };
}
