/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <raylib.h>

#include "./Raylib/Window/Window.hh"
#include "./Raylib/Text/Text.hh"
#include "./Raylib/Texture/Texture.hh"
#include "./Raylib/3DEnvironment/Model3D.hh"
#include "./Raylib/3DEnvironment/Camera.hh"
#include "Raylib/Texture/SpriteSheet.hh"
#include "Raylib/Texture/AnimatedSpriteSheet.hh"

int main(void)
{
    Raylib::Window window(KEY_DELETE, "Zappy", 60);
    Raylib::Camera camera;
    // Raylib::Model3D model("ArcTriomphe.obj", "textures.png", 0, 0, 0, 0, 0, 0, 0.1);
    // Raylib::AnimatedSpriteSheet crocmouQuiDance("spriteSheetDuDemon.png", 270, 60, 15, 18, 50, 50);
    // Raylib::Text jaj("jaj", 20, "default.ttf", 50, 75, 3, BLACK, Raylib::CENTER);
    // Raylib::Texture toothless("toothless-dancing.gif", 50, 50, 0, 1);

    while (!window.myWindowShouldClose())
    {
        window.myBeginDrawing();
            window.myClearBackground();
            camera.begin3DMode();
                // model.ModelDraw();
            // toothless.DrawTexture();
            // jaj.TextDraw();
            camera.end3DMode();
            // crocmouQuiDance.DrawSpriteSheet();
            DrawFPS(10, 10);
        window.myEndDrawing();
    }
    window.myCloseWindow();
    return 0;
}
