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
#include <memory>

int main(int ac, char *av[])
{
    (void)ac;
    try {
        Zappy::GuiSocket sock;
        sock.run(av[1], av[2]);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
