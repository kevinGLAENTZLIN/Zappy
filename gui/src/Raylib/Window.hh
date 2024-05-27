/*
** EPITECH PROJECT, 2024
** Window.hh
** File description:
** Window
*/

#pragma once
#include <raylib.h>
#include <iostream>

namespace Raylib {
    class Window {
        public:
            Window(int width, int height, std::string title);
            ~Window();
            void LoadWindow(int fps, int exitKey);
            void MyBeginDrawing() const;
            void MyEndDrawing() const;
            void MyCloseWindow() const;
            bool MyWindowShouldClose() const;
            void MyClearBackground(Color color) const;

        protected:
        private:
            void MyInitWindow(int width, int height, std::string title) const;
            void MySetTargetFPS(int fps) const;
            void MySetExitKey(int key) const;
            void MyInitAudioDevice() const;
            int _width;
            int _height;
            std::string _title;
    };
}
