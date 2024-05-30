/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** socket.hpp
*/

#pragma once
#include <cstdio>
#include <exception>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <iostream>
#include <vector>

#include "../ErrorGUI.hh"

namespace Zappy {

    class GuiSocket {

        public:
            static std::size_t createSocket(const std::size_t &port, const std::string &ip);
            static void closeSocket(const std::size_t &sock);
            static void sendToServer(const std::size_t &sock, const std::string &msg);
            static std::string receiveFromServer(const std::size_t &socket);
        private:
            static int selectRead(const std::size_t &sock);
    };
}
