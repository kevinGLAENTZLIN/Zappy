/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AI.hpp
*/

#include "Utils/Socket.hpp"
#include "Utils/Utils.hh"
#include <memory>
#include <utility>
#include <sstream>
#include <chrono>

namespace Zappy {

    class AI {

        public:
            AI(void);
            ~AI() = default;
            void checkArg(int argc, char **argv);
            void initAI(const std::string port, const std::string teamName, const std::string ip);
            void run();
            void handleResponse(void);
            void handleCommand(std::string response);
            void handlePriority(std::string response);
            void parseInventory(const std::string &response);
            void handleLook(const std::string &response);
            //void handleDefaultAction(void);
            void initConnection(void);

        private:
            std::string _ip;
            std::string _port;
            std::string _teamName;
            std::unique_ptr<Zappy::Socket> _clientSocket;
            std::vector<std::string> _priorityQueue;
            std::string _lastCommand;
            std::chrono::steady_clock::time_point _lastInventoryTime;
            bool _isAlive;
            int _food;
            int _fd;
            int _worldX;
            int _worldY;
            bool _isImportant;
            int _currentLevel;
    };
}
