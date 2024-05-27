/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Screen
*/

#include "Screen.hh"

extern "C" {

    int Raylib::Screen::myGetScreenWidth()
    {
        return GetScreenWidth();
    }

    int Raylib::Screen::myGetScreenHeight()
    {
        return GetScreenHeight();
    }

}
