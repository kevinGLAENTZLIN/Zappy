/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AI.hpp
*/

#include "Utils/Socket.hpp"
#include <memory>

namespace Zappy {

    class AI {

        public:
            AI(const std::string port, const std::string teamName, const std::string ip);
            ~AI() = default;
            void run();

        private:
            std::string _ip;
            std::string _port;
            std::string _teamName;
            bool _isAlive;
            std::unique_ptr<Zappy::Socket> _clientSocket;

    };
}
