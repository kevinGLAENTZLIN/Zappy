/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Screen
*/

#include "Screen.hh"

extern "C" {

    int Raylib::Screen::MyGetScreenWidth()
    {
        return GetScreenWidth();
    }

    int Raylib::Screen::MyGetScreenHeight()
    {
        return GetScreenHeight();
    }

}
