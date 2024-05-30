/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** SceneFactory
*/

#include "SceneFactory.hh"
#include "MainMenu/MainMenu.hh"
#include "OptionMenu/OptionMenu.hh"
#include "Game/Game.hh"

std::unique_ptr<Zappy::IScene> Zappy::SceneFactory::createMainMenu(std::shared_ptr<CommonElements> commonElements)
{
    return std::make_unique<MainMenu>(commonElements);
}

std::unique_ptr<Zappy::IScene> Zappy::SceneFactory::createOptionMenu(std::shared_ptr<CommonElements> commonElements)
{
    return std::make_unique<OptionMenu>(commonElements);
}

std::unique_ptr<Zappy::IScene> Zappy::SceneFactory::createGame(std::shared_ptr<CommonElements> commonElements)
{
    return std::make_unique<Game>(commonElements);
}
