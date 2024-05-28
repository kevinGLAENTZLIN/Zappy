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
            Window(const int &exitKey, const std::string &title, const int &fps = 60);
            ~Window();
            void LoadWindow(const int &fps, const int &exitKey);
            void myBeginDrawing() const;
            void myEndDrawing() const;
            void myCloseWindow() const;
            bool myWindowShouldClose() const;
            void myClearBackground() const;

        protected:
        private:
            void myInitWindow(const int &width, const int &height, const std::string &title) const;
            void mySetTargetFPS(const int &fps) const;
            void mySetExitKey(const int &key) const;
            void myInitAudioDevice() const;
            void setFullScreen() const;
    };
}
