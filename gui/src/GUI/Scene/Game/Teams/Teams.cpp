/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Teams
*/

#include "Teams.hh"
#include <memory>
#include <raylib.h>

Zappy::Teams::Teams(const std::string &teamName, std::size_t teamNb):
    _playersLvlText(), _playersLvlNb(), _teamName({teamName, nullptr}),
    _background(nullptr), _tooManyTeams(false)
{
    std::string teamNameWoQuotes = teamName;

    teamNameWoQuotes.erase(0, 1);
    teamNameWoQuotes.pop_back();
    _background = std::make_shared<Raylib::Texture>("gui/assets/TeamInfo.png");
    _scale =  (Raylib::Screen::myGetMonitorWidth() / 4.0f) / _background->GetTexture().width;
    _background->setScale(_scale);
    _background->setPosition(0, (_background->GetTexture().height * _scale) * (teamNb - 1) + 25 * teamNb);
    if (_background->GetTexture().height * _scale * teamNb > Raylib::Screen::myGetMonitorHeight()) {
        _tooManyTeams = true;
        return;
    }
    _teamName.second = std::make_shared<Raylib::Text>(teamNameWoQuotes, 50,
        "gui/assets/Futura Condensed Medium.ttf", (static_cast<int>(_background->GetTexture().width * _scale) >> 1),
        _background->getPosition().y + _background->GetTexture().height * _scale * 0.1, 2, WHITE, Raylib::PIXEL);
    _nbPlayers = std::make_shared<Raylib::Text>("Players on the team: 0", 40,
        "gui/assets/Futura Condensed Medium.ttf", _background->GetTexture().width * _scale / 6.0f * 1.01,
        _background->getPosition().y + _background->GetTexture().height * _scale * 0.35, 2, WHITE,
        Raylib::PIXEL, Raylib::LEFT);
    addPlayerLvl();
}

Zappy::Teams::~Teams()
{
}

std::string Zappy::Teams::getTeamName() const
{
    return _teamName.first;
}

void Zappy::Teams::Draw()
{
    if (_tooManyTeams)
        return;
    _background->DrawTexture();
    _teamName.second->TextDraw();
    _nbPlayers->TextDraw();
    for (std::size_t i = 0; i < 8; i++) {
        _playersLvlText[i]->TextDraw();
    }
}

void Zappy::Teams::Update()
{
    _playersLvlNb[0]++;
    _nbPlayers->setText("Players on the team: " + std::to_string(_playersLvlNb[0]));
    _playersLvlText[0]->setText("Lvl 1: " + std::to_string(_playersLvlNb[0]));
}

void Zappy::Teams::Update(std::size_t playerNewLvl)
{
    std::cout << "Player new lvl: " << playerNewLvl << std::endl;
    _playersLvlNb[playerNewLvl - 2]--;
    _playersLvlNb[playerNewLvl - 1]++;
    _playersLvlText[playerNewLvl - 2]->setText(TextFormat("Lvl %d: %d", playerNewLvl - 1,
                                                          _playersLvlNb[playerNewLvl - 2]));
    _playersLvlText[playerNewLvl - 1]->setText(TextFormat("Lvl %d: %d", playerNewLvl,
                                                          _playersLvlNb[playerNewLvl - 1]));
}

void Zappy::Teams::addPlayerLvl()
{
    double posY = _background->getPosition().y + _background->GetTexture().height * _scale * 0.55;

    for (std::size_t i = 0; i < 8; i++) {
        _playersLvlNb.emplace_back(0);
        if (i % 4 == 0 && i != 0)
            posY += _background->GetTexture().height * _scale * 0.15;
        _playersLvlText.emplace_back(std::make_shared<Raylib::Text>("Lvl " + std::to_string(i + 1) + ": 0", 35,
            "gui/assets/Futura Condensed Medium.ttf", _background->GetTexture().width * _scale * ((i % 4 + 1) / 6.0f) * 1.1,
            posY, 2, WHITE, Raylib::PIXEL, Raylib::LEFT));
    }
}
