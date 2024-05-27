/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

extern "C" {
    #include <raylib.h>
}
#include "./Raylib/Window.hh"


int main(void)
{
    Raylib::Window window(800, 450, "Zappy");
    window.LoadWindow(60, KEY_DELETE);

    while (!window.MyWindowShouldClose())
    {
        window.MyBeginDrawing();
            window.MyClearBackground(RAYWHITE);
            DrawText("Hello World", 190, 200, 20, LIGHTGRAY);
        window.MyEndDrawing();
    }
    window.MyCloseWindow();
    return 0;
}
