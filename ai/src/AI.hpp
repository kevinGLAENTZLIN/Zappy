/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AI.hpp
*/

#include "Utils/Socket.hpp"
#include <map>
#include <memory>
#include <utility>

namespace Zappy {

    class AI {

        public:
            AI(const std::string port, const std::string teamName, const std::string ip);
            ~AI();
            void run();

        private:
            std::string _ip;
            std::string _port;
            std::string _teamName;
            std::unique_ptr<Zappy::Socket> _clientSocket;
            std::vector<std::string> _commands;
            bool _isAlive;

    };
}
