/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <raylib.h>

#include "./Raylib/Window.hh"
#include "./Raylib/Text/Text.hh"
#include "./Raylib/Texture/Texture.hh"

int main(void)
{
    Raylib::Window window(KEY_DELETE, "Zappy", 60);
    // Raylib::Text jaj("jaj", 20, "default.ttf", 50, 75, 3, BLACK, Raylib::CENTER);
    // Raylib::Texture toothless("toothless-dancing.gif", 50, 50, 0, 1);

    while (!window.myWindowShouldClose())
    {
        window.myBeginDrawing();
            // toothless.DrawTexture();
            window.myClearBackground();
            // jaj.TextDraw();
        window.myEndDrawing();
    }
    window.myCloseWindow();
    return 0;
}
