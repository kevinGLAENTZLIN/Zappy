/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** GUI
*/

#include "GUI.hh"
#include "../ErrorGUI.hh"
#include "../Utils/Utils.hh"
#include "../Utils/GuiSocket.hh"

Zappy::GUI::GUI(const std::vector<std::string> &args)
{
    handleArguments(args);
    runGUI();
}

Zappy::GUI::~GUI()
{
}

void Zappy::GUI::handleArguments(const std::vector<std::string> &args)
{
    if (args.size() == 2 && (args[1] == "-h" || args[1] == "--help" || args[1] == "-help"))
        throw ErrorGUI("USAGE:\n\t./zappy_gui -p _port -h machine");
    if (args.size() != 5)
        throw ErrorGUI(ARG_ERROR, "Invalid number of arguments. Please use -h for help.");
    if (args[1] != "-p" || args[3] != "-h")
        throw ErrorGUI(ARG_ERROR, "Invalid arguments. Please use -h for help.");
    if (!Zappy::Utils::isNumber(args[2]))
        throw ErrorGUI(ARG_ERROR, "Invalid port.");
    _port = std::stoi(args[2]);
    if (_port < 1024 || _port > 65535)
        throw ErrorGUI(ARG_ERROR, "Invalid port number.");
    if (!Zappy::Utils::isIp(args[4]))
        throw ErrorGUI(ARG_ERROR, "Invalid IP address.");
    _ip = args[4];
    if (args[4] == "localhost")
        _ip = "127.0.0.1";
}

void Zappy::GUI::runGUI()
{
    std::string serverInput;

    _window = std::make_unique<Raylib::Window>(KEY_BACKSPACE, "Zappy");
    _commonElements = std::make_shared<CommonElements>();
    _commonElements->setPort(_port);
    _commonElements->setIp(_ip);
    initScenes();
    _commonElements->getMusic().play();
    _commonElements->getMusic().setVolume(0.5);
    while (_window->myWindowShouldClose() == false) {
        _commonElements->drawFPS();
        _commonElements->getMusic().updateMusic();
        _scenes[_commonElements->getCurrentScene()]->computeLogic();
        _window->myBeginDrawing();
            _window->myClearBackground();
            _scenes[_commonElements->getCurrentScene()]->displayElements();
        _window->myEndDrawing();
    }
}

void Zappy::GUI::initScenes()
{
    _scenes.push_back(SceneFactory::createMainMenu(_commonElements));
    _scenes.push_back(SceneFactory::createOptionMenu(_commonElements));
    _scenes.push_back(SceneFactory::createGame(_commonElements));
}
