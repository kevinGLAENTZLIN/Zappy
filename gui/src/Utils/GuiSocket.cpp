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

Zappy::GuiSocket::GuiSocket()
{
    createSocket();
}

Zappy::GuiSocket::~GuiSocket()
{
    closeSocket();
}

int Zappy::GuiSocket::getSocket() const
{
    return _socket;
}

int &Zappy::GuiSocket::getSocket()
{
    return _socket;
}

void Zappy::GuiSocket::run(std::string port, std::string addr)
{
    std::string response;
    std::string team = "GRAPHICS";
    int fd = 0;

    connectSocket(port, addr);
    while (true) {
        selectSocket();
        fd = getSocket();
        fd >> response;
        if (response == "WELCOME\n")
            fd << team;
        std::cout << "response -> " << response << std::endl;
    }
}

extern "C" {

    void Zappy::GuiSocket::createSocket(void)
    {
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket == -1)
            Zappy::ErrorGUI(SocketError, "socket: " + std::string(strerror(errno)));
    }

    int Zappy::GuiSocket::selectSocket(void)
    {
        int ret = 0;

        FD_ZERO(&_rfds);
        FD_ZERO(&_wfds);
        FD_SET(_socket, &_rfds);
        ret = select(_socket + 1, &_rfds, &_wfds, NULL, NULL);
        if (ret == -1)
            throw Zappy::ErrorGUI(SocketError, "select: " + std::string(strerror(errno)));
        return ret;
    }

    void Zappy::GuiSocket::closeSocket(void)
    {
        close(_socket);
    }

    void Zappy::GuiSocket::connectSocket(const std::string port, const std::string serverAdress)
    {
        struct sockaddr_in sock_serv;

        std::cout << port << std::endl;
        std::cout << serverAdress << std::endl;

        sock_serv.sin_family = AF_INET;
        sock_serv.sin_port = htons(atoi(port.c_str()));
        sock_serv.sin_addr.s_addr = inet_addr(serverAdress.c_str());
        if (connect(_socket, (struct sockaddr *) &sock_serv, sizeof(sock_serv)) == -1)
            throw ErrorGUI(SocketError, "connect: " + std::string(strerror(errno)));
    }
};

int &Zappy::operator<<(int &sock, const std::string &val)
{
    if (write(sock, val.c_str(), sizeof(char) * (val.length() + 1)) == -1)
        throw Zappy::ErrorGUI(SocketError, "write: " + std::string(strerror(errno)));
    return sock;
}

int &Zappy::operator>>(int &sock, std::string &val)
{
    char buffer[40000];

    if (read(sock, buffer, sizeof(char) * 40000) == -1)
        throw Zappy::ErrorGUI(SocketError, "read: " + std::string(strerror(errno)));
    val = std::string(buffer);
    return sock;
}
