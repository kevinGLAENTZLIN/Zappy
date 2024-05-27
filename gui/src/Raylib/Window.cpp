/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Window
*/

#include "Window.hh"

Raylib::Window::Window(int fps, int exitKey, std::string title)
{
    myInitWindow(800, 450, title);
    LoadWindow(fps, exitKey);
}

Raylib::Window::~Window()
{
}

void Raylib::Window::LoadWindow(int fps, int key)
{
    mySetTargetFPS(fps);
    mySetExitKey(key);
    setFullScreen();
    myInitAudioDevice();
}

extern "C" {

    void Raylib::Window::myInitWindow(int width, int height, std::string title) const
    {
        InitWindow(width, height, title.c_str());
    }

    bool Raylib::Window::myWindowShouldClose() const
    {
        return WindowShouldClose();
    }

    void Raylib::Window::mySetTargetFPS(int fps) const
    {
        SetTargetFPS(fps);
    }

    void Raylib::Window::mySetExitKey(int key) const
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
