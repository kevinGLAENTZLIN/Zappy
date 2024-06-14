/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Teams
*/


#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "../../../../Raylib/Raylib.hh"

namespace Zappy {
    class Teams {
    public:
        Teams(const std::string &teamName, std::size_t teamNb);
        ~Teams();

        std::string getTeamName() const;

        void Draw();
        void Update();
        void Update(std::size_t playerNewLvl);
    private:
        void addPlayerLvl();
        std::vector<std::shared_ptr<Raylib::Text>> _playersLvlText;
        std::vector<std::size_t> _playersLvlNb;
        std::pair<std::string, std::shared_ptr<Raylib::Text>> _teamName;
        std::shared_ptr<Raylib::Text> _nbPlayers;
        std::shared_ptr<Raylib::Texture> _background;
        bool _tooManyTeams;
        double _scale;
    };
}
