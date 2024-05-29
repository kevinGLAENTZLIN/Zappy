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

    int Raylib::Screen::myGetMonitorWidth()
    {
        return GetMonitorWidth(0);
    }

    int Raylib::Screen::myGetMonitorHeight()
    {
        return GetMonitorHeight(0);
    }

}
