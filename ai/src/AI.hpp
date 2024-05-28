/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AI.hpp
*/

#include "Utils/Socket.hpp"
#include "Utils/Utils.hh"
#include <map>
#include <memory>
#include <sstream>
#include <regex>
#include <utility>

namespace Zappy {

    class AI {

        public:
            AI(void);
            ~AI() = default;
            void checkArg(int argc, char **argv);
            void initAI(const std::string port, const std::string teamName, const std::string ip);
            void run();
            void handleResponse(int fd);
            void handleCommand(std::string response, int fd);
            void handlePriority(std::string response, int fd);
            void parseInventory(const std::string &response);
            void handleDefaultAction(int fd);

        private:
            std::string _ip;
            std::string _port;
            std::string _teamName;
            std::unique_ptr<Zappy::Socket> _clientSocket;
            std::vector<std::string> _commands;
            std::map<std::string, int> _commandPriority;
            bool _isAlive;
            int _food;
            int _linemate;
            int _deraumere;
            int _sibur;
            int _worldX;
            int _worldY;
            int _mendiane;
            int _phiras;
            bool _isImportant;
            int _thystame;
            int _currentLevel;
    };
}

