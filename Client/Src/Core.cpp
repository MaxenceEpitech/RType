#include "Core.hpp"

namespace RType {

    void Core::initUDP() {
        auto UDPAddress = sf::IpAddress((argv.size() >= 2) ? argv[1] : "127.0.0.1");
        auto UDPPort = (argv.size() >= 3)
                       ? static_cast<unsigned short>(std::stoul(argv[2]))
                       : 1234;

        std::cout << "Connecting to UDP " << UDPAddress << ":" << UDPPort << std::endl;
        _Client = new UDPClient(UDPPort, UDPAddress);
        _font.loadFromFile("Assets/Fonts/elixia.ttf");
        _hud.setFont(_font);
        _hud.setCharacterSize(24);
        _hud.setFillColor(sf::Color::White);
    }

    void Core::setGame() {
        _Game = new Game(_Window, _WindowX, _WindowY);
        initUDP();
    }

    void Core::handleGraphicalPacket(sf::Packet packet, int turn) {
        if (turn == 0) {
            _Window.draw(_Game->getText().getGameSprite(Textures::BACKGROUND));
        }
        Packet::Graphic graphic = Packet::Unpacker::UnpackGraphics(packet);
        try {
            _Game->getText().setSpritePos(graphic.index, graphic.position);
            _Window.draw(_Game->getText().getGameSprite(graphic.index));
            if (_lost)
                _Window.draw(_Game->getText().getGameSprite(Textures::GAMEOVER));
            _Window.draw(_hud);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void Core::interpretPacket(sf::Packet packet, int turn) {
        Packet::Health packetHealth;
        switch (Packet::GetEnum(packet)) {
            case Packet::GRAPHIC:
                handleGraphicalPacket(packet, turn);
                break;
            case Packet::GAME_OVER:
                _lost = true;
                //std::cout << "GAME OVER, you lost" << std::endl;
                break;
            case Packet::HEALTH:
                packetHealth = Packet::Unpacker::UnpackHealth(packet);
                _hud.setString(std::string("Health  ") + std::to_string(packetHealth.currentHealth) + "/"
                + std::to_string(packetHealth.maxHealth) + "  Level " + std::to_string(packetHealth.level));
                break;
            default:
                break;
        }
    }

    void Core::gameLoop() {
        int turn = 0;
        EventHandler eventHandler(*_Client);
        while (_Window.isOpen()) {
            eventHandler.HandleEvents(_Window);
            sf::Packet packet;
            while (_Client->Receive(packet)) {
                //std::cerr << "Got a packet, time to switch case" << std::endl;
                interpretPacket(packet, turn);
                turn = 1;
            }
            if (turn == 1)
                _Window.display();
            turn = 0;
        }
        _Client->Disconnect();
        std::cout << "Disconnected from Server" << std::endl;
    }

    void Core::clientLoop(int value) {
        try {
            Packet::Lobbies lobbies = _Client->getLobbies();
            auto clientNumber = 0;
            if (value != -1) {
                if (lobbies[value] != Packet::MAX_CLIENT) {
                    clientNumber = _Client->Connect(value);
                } else
                    for (size_t i = 0; i < lobbies.size(); i++)
                        if (lobbies[i] < 4)
                            clientNumber = _Client->Connect(i);
            }
            if (clientNumber == 0 || value == -1)
                clientNumber = _Client->Create();
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        gameLoop();
    }

    void Core::joinMenu() {
        setGame();
        Packet::Lobbies lobbies = _Client->getLobbies();
        _Window.draw(_Game->getText().getGameSprite(Textures::BACKGROUND));
        if (_Game->handleLobbies(lobbies) == -1)
            clientLoop(-1);
        else
            clientLoop(_Game->joinLobby(lobbies));
    }

    Core::Core(std::vector<std::string> &argv, const int winX, const int winY,
               const std::string &_windowName)
            : argv(argv), _Window(sf::VideoMode(winX, winY), _windowName, sf::Style::Default), _WindowX(winX),
              _WindowY(winY), _Frames(60) {
        Menu menu(_Window, _WindowX, _WindowY);
        auto retval = menu.menuLoop();
        switch (retval) {
            case -1:
                _Window.close();
                break;
            case 1:
                joinMenu();
                break;
            case 2:
                setGame();
                clientLoop(-1);
                break;
            default:
                break;
        }
        std::cout << "The end" << std::endl;
    }

} // namespace RType
