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
    Raylib::Window window(60, KEY_DELETE, "Zappy");

    while (!window.myWindowShouldClose())
    {
        window.myBeginDrawing();
            window.myClearBackground();
            DrawText("Hello World", 190, 200, 20, LIGHTGRAY);
        window.myEndDrawing();
    }
    window.myCloseWindow();
    return 0;
}
