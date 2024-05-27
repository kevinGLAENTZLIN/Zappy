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
            Window(int fps, int exitKey, std::string title);
            ~Window();
            void LoadWindow(int fps, int exitKey);
            void myBeginDrawing() const;
            void myEndDrawing() const;
            void myCloseWindow() const;
            bool myWindowShouldClose() const;
            void myClearBackground() const;

        protected:
        private:
            void myInitWindow(int width, int height, std::string title) const;
            void mySetTargetFPS(int fps) const;
            void mySetExitKey(int key) const;
            void myInitAudioDevice() const;
            void setFullScreen() const;
    };
}
