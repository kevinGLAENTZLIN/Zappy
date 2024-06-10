/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Network
*/


#pragma once

#include "../../../CommonElements/CommonElements.hh"
#include "../../../../Utils/GuiSocket.hh"
#include "../Elements.hh"

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <queue>
#include <map>

namespace Zappy {
    class Game;
    class Network {
    public:
        Network(std::shared_ptr<CommonElements> commonElements, Game &game);
        ~Network();

        void checkServer();
        void sendQueueToServer();
        void addToQueue(const std::string &command);
    private:
        void initCommands();

        void welcome(const std::string &args);
        void msz(const std::string &args);
        void bct(const std::string &args);
        void tna(const std::string &args);
        void pnw(const std::string &args);
        void ppo(const std::string &args);
        void plv(const std::string &args);
        void pin(const std::string &args);
        void pex(const std::string &args);
        void pbc(const std::string &args);
        void pic(const std::string &args);
        void pie(const std::string &args);
        void pfk(const std::string &args);
        void pdr(const std::string &args);
        void pgt(const std::string &args);
        void pdi(const std::string &args);
        void enw(const std::string &args);
        void ebo(const std::string &args);
        void edi(const std::string &args);
        void sgt(const std::string &args);
        void sst(const std::string &args);
        void seg(const std::string &args);
        void smg(const std::string &args);

        std::map<std::string, std::function<void(const std::string &)>> _commands;
        std::shared_ptr<CommonElements> _commonElements;
        std::queue<std::string> _commandsQueue;
        bool _isConnected;
        Game &_game;
    };
}
