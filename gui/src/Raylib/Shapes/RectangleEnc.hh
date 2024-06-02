/*
** EPITECH PROJECT, 2024
** RectangleEnc.hh
** File description:
** RectangleEnc
*/

#pragma once
#include <optional>
#include <raylib.h>
#include <utility>

namespace Raylib {
    class RectangleEnc {
        public:
            RectangleEnc();
            RectangleEnc(double x, double y, double width, double height, Color color);
            ~RectangleEnc();

            std::pair<double, double> getPosition() const;
            std::pair<double, double> getSize() const;
            Color getColor() const;
            Rectangle getRectangle() const;

            void setPosition(double x, double y);
            void setSize(double width, double height);

            void myDrawRectangle() const;

        private:
            double _x;
            double _y;
            double _width;
            double _height;
            Color _color;
    };
}
