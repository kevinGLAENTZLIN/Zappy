/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AI.hpp
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>

#include "Utils/Socket.hpp"
#include "Utils/Utils.hh"
#include "ErrorAI.hpp"

#define FORWARD 0
#define INVENTORY 1
#define LOOK 2
#define RIGHT 3
#define FORK 4
#define INCANTATION 5
#define BROADCAST 6
#define CONNECT_NBR 7
#define EJECT 8
#define TAKE_OBJECT 9

namespace Zappy {
    class AI {
        public:
            AI();
            void checkArg(int argc, char **argv);
            void initAI(const std::string port, const std::string teamName, const std::string ip);
            void initConnection(void);
            void run(void);

        private:
            void handleResponse(void);
            void handleLook(const std::string &response);
            void parseInventory(const std::string &response);

            void sendCommand(const std::string &command);

            void handleInventoryResponse(const std::string &response);
            void handleLookResponse(const std::string &response);
            void handleDefaultResponse(const std::string &response);
            void handleTakeObjectResponse(const std::string &response);

            std::string _port;
            std::string _ip;
            std::string _teamName;
            std::unique_ptr<Zappy::Socket> _clientSocket;
            bool _isAlive;
            int _currentLevel;
            int _food;
            int _numberCmd = 0;
            int _fd;
            std::vector<std::string> _commands;
            std::queue<std::string> _commandQueue;
    };
}
