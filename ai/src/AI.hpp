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
#include <chrono>
#include <thread>

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
#define SET_OBJECT 10
#define LEFT 11

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
            void handleBroadcast(const std::string &response);
            void parseInventory(const std::string &response);
            bool handleIncantation(int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);
            void handlePlayerMove(int tileIndex);
            void takeObject(const std::string &object);
            void handleUniqueCommand(const std::string &serverResponse, const std::string &response);

            void sendCommand(const std::string &command, bool isObject, const std::string &object = "");
            void moveToBroadcastPosition(int position);
            void handleTakeObjectResponse(const std::string &response);

            bool _isAlive;
            bool _isIncantation;
            bool _isBroadcast;
            int _currentLevel;
            int _nbPlayer;
            int _food;
            int _numberCmd;
            int _fd;
            int _clientNumber;
            int _sizeWorldX;
            int _sizeWorldY;
            std::string _port;
            std::string _ip;
            std::string _teamName;
            std::unique_ptr<Zappy::Socket> _clientSocket;
            std::vector<std::string> _commands;
            std::queue<std::string> _commandQueue;
    };
}
