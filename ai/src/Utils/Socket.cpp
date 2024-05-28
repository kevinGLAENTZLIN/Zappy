/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** socket.cpp
*/

#include "Socket.hpp"
#include <cstdio>
#include <cstring>
#include <exception>
#include <iostream>

Zappy::Socket::Socket()
{
    createSocket();
}

Zappy::Socket::~Socket()
{
    closeSocket();
}

int Zappy::Socket::getSocket() const
{
    return _socket;
}

int &Zappy::Socket::getSocket()
{
    return _socket;
}

extern "C" {

    void Zappy::Socket::createSocket(void)
    {
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket == -1)
            Zappy::ErrorAI(SocketError, "socket: " + std::string(strerror(errno)));
    }

    int Zappy::Socket::selectSocket(void)
    {
        int ret = 0;

        FD_ZERO(&_rfds);
        FD_ZERO(&_wfds);
        FD_SET(_socket, &_rfds);
        ret = select(_socket + 1, &_rfds, &_wfds, NULL, NULL);
        if (ret == -1)
            throw Zappy::ErrorAI(SocketError, "select: " + std::string(strerror(errno)));
        return ret;
    }

    void Zappy::Socket::closeSocket(void)
    {
        close(_socket);
    }

    void Zappy::Socket::connectSocket(const std::string port, const std::string serverAdress)
    {
        struct sockaddr_in sock_serv;

        std::cout << port << std::endl;
        std::cout << serverAdress << std::endl;

        sock_serv.sin_family = AF_INET;
        sock_serv.sin_port = htons(atoi(port.c_str()));
        sock_serv.sin_addr.s_addr = inet_addr(serverAdress.c_str());
        if (connect(_socket, (struct sockaddr *) &sock_serv, sizeof(sock_serv)) == -1)
            throw ErrorAI(SocketError, "connect: " + std::string(strerror(errno)));
    }
};

int &Zappy::operator<<(int &sock, const std::string &val)
{
    if (write(sock, val.c_str(), val.length()) == -1)
        throw Zappy::ErrorAI(SocketError, "write: " + std::string(strerror(errno)));
    return sock;
}

int &Zappy::operator>>(int &sock, std::string &val)
{
    char buffer[40000];
    ssize_t byte = read(sock, buffer, sizeof(buffer) - 1);

    if (byte == -1)
        throw Zappy::ErrorAI(SocketError, "read: " + std::string(strerror(errno)));
    buffer[byte] = '\0';
    val = std::string(buffer);
    return sock;
}