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
#include "./Utils/GuiSocket.hh"
#include "./ErrorGUI.hh"
#include "./GUI/GUI.hh"

int main(int ac, char *av[])
{
    SetTraceLogLevel(LOG_ERROR);
    std::vector<std::string> args(av, av + ac);
    try {
        Zappy::GUI gui(args);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
