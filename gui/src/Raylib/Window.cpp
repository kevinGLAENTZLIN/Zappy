/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Window
*/

#include "Window.hh"

Raylib::Window::Window(int width, int height, std::string title):
    _width(width), _height(height), _title(title)
{
    MyInitWindow(width, height, title);
}

Raylib::Window::~Window()
{
}

void Raylib::Window::LoadWindow(int fps, int key)
{
    MySetTargetFPS(fps);
    MySetExitKey(key);
    MyInitAudioDevice();
}

extern "C" {

    void Raylib::Window::MyInitWindow(int width, int height, std::string title) const
    {
        InitWindow(width, height, title.c_str());
    }

    bool Raylib::Window::MyWindowShouldClose() const
    {
        return WindowShouldClose();
    }

    void Raylib::Window::MySetTargetFPS(int fps) const
    {
        SetTargetFPS(fps);
    }

    void Raylib::Window::MySetExitKey(int key) const
    {
        SetExitKey(key);
    }

    void Raylib::Window::MyBeginDrawing() const
    {
        BeginDrawing();
    }

    void Raylib::Window::MyClearBackground(Color color) const
    {
        ClearBackground(color);
    }

    void Raylib::Window::MyEndDrawing() const
    {
        EndDrawing();
    }

    void Raylib::Window::MyCloseWindow() const
    {
        CloseWindow();
    }

    void Raylib::Window::MyInitAudioDevice() const
    {
        InitAudioDevice();
    }

}
