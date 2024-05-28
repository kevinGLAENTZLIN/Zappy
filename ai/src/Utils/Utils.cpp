/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** utils.cpp
*/

#include "Utils.hh"

extern "C" {
    pid_t Zappy::Utils::process(void)
    {
        pid_t pid = fork();
        return pid;
    }
}