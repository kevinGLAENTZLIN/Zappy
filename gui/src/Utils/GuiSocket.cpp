/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** socket.cpp
*/

#include "GuiSocket.hh"
#include <cstdio>
#include <cstring>
#include <exception>
#include <iostream>

extern "C" {
    std::size_t Zappy::GuiSocket::createSocket(const std::size_t &port, const std::string &ip)
    {
        struct sockaddr_in sock_serv;
        int sock = socket(AF_INET, SOCK_STREAM, 0);

        if (sock > 65535 || sock < 0)
            Zappy::ErrorGUI(SOCKET_ERROR, "socket: " + std::string(strerror(errno)));
        sock_serv.sin_family = AF_INET;
        sock_serv.sin_port = htons(port);
        sock_serv.sin_addr.s_addr = inet_addr(ip.c_str());
        if (connect(sock, (struct sockaddr *) &sock_serv, sizeof(sock_serv)) == -1)
            throw ErrorGUI(SOCKET_ERROR, "connect: " + std::string(strerror(errno)));
        return sock;
    }


    void Zappy::GuiSocket::closeSocket(const std::size_t &socket)
    {
        close(socket);
    }

    void Zappy::GuiSocket::sendToServer(const std::size_t &socket, const std::string &msg)
    {
        if (send(socket, msg.c_str(), sizeof(char) * (msg.length() + 1), 0) == -1)
            throw Zappy::ErrorGUI(SOCKET_ERROR, "send: " + std::string(strerror(errno)));
    }

    std::string Zappy::GuiSocket::receiveFromServer(const std::size_t &socket)
    {
        char buffer;
        std::string newBuff;

        if (selectRead(socket) == -1)
            return "";
        while (read(socket, &buffer, sizeof(buffer))) {
            if (buffer == '\n')
                break;
            newBuff += buffer;
        }
        return newBuff;
    }

    int Zappy::GuiSocket::selectRead(const std::size_t &sock)
    {
        int ret = 0;
        struct timeval timeoutStruct;
        fd_set _rfds;

        FD_SET(sock, &_rfds);
        timeoutStruct.tv_sec = 0;
        timeoutStruct.tv_usec = 100;
        ret = select(sock + 1, &_rfds, NULL, NULL, &timeoutStruct);
        if (ret == 0)
            return -1;
        FD_ZERO(&_rfds);
        return ret;
    }
};
