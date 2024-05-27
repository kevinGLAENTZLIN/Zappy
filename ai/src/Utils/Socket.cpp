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

    void Zappy::Socket::bindSocket(void)
    {
        struct sockaddr_un server_addr;

        server_addr.sun_family = AF_INET;
        strcpy(server_addr.sun_path, "test");
        if (bind(_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
            closeSocket();
            throw Zappy::ErrorAI(SocketError, "bind: " + std::string(strerror(errno)));
        }
        if (listen(_socket, FD_SETSIZE) == -1) {
            closeSocket();
            throw Zappy::ErrorAI(SocketError, "listen: " + std::string(strerror(errno)));
        }
    }

    void Zappy::Socket::createSocket(void)
    {
        _socket = socket(AF_UNIX, SOCK_STREAM, 0);
        if (_socket == -1)
            Zappy::ErrorAI(SocketError, "socket: " + std::string(strerror(errno)));
    }

    int Zappy::Socket::acceptConnection(void)
    {
        struct sockaddr_un client_addr;
        socklen_t client_len = sizeof(client_addr);
        int clientSocket;

        clientSocket = accept(_socket, (struct sockaddr *) &client_addr, &client_len);
        if (clientSocket == -1)
            throw Zappy::ErrorAI(SocketError, "accept: " + std::string(strerror(errno)));
        return clientSocket;
    }

    int Zappy::Socket::selectSocket(void)
    {
        struct timeval timeoutStruct;
        int ret = 0;

        ret = select(42, &_rfds, &_wfds, NULL, NULL);
        if (ret == -1)
            throw Zappy::ErrorAI(SocketError, "select: " + std::string(strerror(errno)));
        return ret;
    }

    void Zappy::Socket::closeSocket(void)
    {
        close(_socket);
    }

    void Zappy::Socket::connectSocket(std::string socketName)
    {
        struct sockaddr_un server_addr;

        server_addr.sun_family = AF_UNIX;
        strcpy(server_addr.sun_path, socketName.c_str());
        if (connect(_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
            throw ErrorAI(SocketError, "connect: " + std::string(strerror(errno)));
    }
};

int &Zappy::operator<<(int &sock, const std::string &val)
{
    if (write(sock, val.c_str(), sizeof(char) * (val.length() + 1)) == -1)
        throw Zappy::ErrorAI(SocketError, "write: " + std::string(strerror(errno)));
    return sock;
}

int &Zappy::operator>>(int &sock, std::string &val)
{
    char buffer[40000];

    if (read(sock, buffer, sizeof(char) * 40000) == -1)
        throw Zappy::ErrorAI(SocketError, "read: " + std::string(strerror(errno)));
    val = std::string(buffer);
    return sock;
}
