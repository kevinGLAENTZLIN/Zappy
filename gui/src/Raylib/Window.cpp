/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Window
*/

#include "Window.hh"

Raylib::Window::Window(const int &exitKey, const std::string &title, const int &fps)
{
    myInitWindow(800, 450, title);
    LoadWindow(fps, exitKey);
}

Raylib::Window::~Window()
{
}

void Raylib::Window::LoadWindow(const int &fps, const int &key)
{
    mySetTargetFPS(fps);
    mySetExitKey(key);
    setFullScreen();
    myInitAudioDevice();
}

extern "C" {

    void Raylib::Window::myInitWindow(const int &width, const int &height, const std::string &title) const
    {
        InitWindow(width, height, title.c_str());
    }

    bool Raylib::Window::myWindowShouldClose() const
    {
        return WindowShouldClose();
    }

    void Raylib::Window::mySetTargetFPS(const int &fps) const
    {
        SetTargetFPS(fps);
    }

    void Raylib::Window::mySetExitKey(const int &key) const
    {
        SetExitKey(key);
    }

    void Raylib::Window::myBeginDrawing() const
    {
        BeginDrawing();
    }

    void Raylib::Window::myClearBackground() const
    {
        ClearBackground(RAYWHITE);
    }

    void Raylib::Window::myEndDrawing() const
    {
        EndDrawing();
    }

    void Raylib::Window::myCloseWindow() const
    {
        CloseWindow();
    }

    void Raylib::Window::myInitAudioDevice() const
    {
        InitAudioDevice();
    }

    void Raylib::Window::setFullScreen() const
    {
        if (IsWindowFullscreen() == false)
            ToggleFullscreen();
    }

}
