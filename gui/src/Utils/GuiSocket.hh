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
            GuiSocket(void);
            ~GuiSocket();
            int getSocket() const;
            int &getSocket();
            int selectSocket(void);
            void connectSocket(const std::string port, const std::string serverAdress);
            void run();

        private:
            void createSocket(void);
            void closeSocket(void);
            int _socket;
            fd_set _rfds;
            fd_set _wfds;

    };

    int &operator<<(int &sock, const std::string &val);
    int &operator>>(int &sock, std::string &val);
}
