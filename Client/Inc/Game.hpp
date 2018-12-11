#ifndef GAME_HPP

#include "EventHandler.hpp"
#include "Textures.hpp"
#include <iostream>

namespace RType {

class Game {
public:
    Game(sf::RenderWindow&, const int, const int);
    ~Game() = default;
    void loadAllSprites();
    int joinLobby(Packet::Lobbies&);
    int displayLobbies(Packet::Lobbies&);
    int noLobbies();
    int handleLobbies(Packet::Lobbies&);
    Textures& getText();
    void drawText(sf::Font, std::string, sf::Vector2f);
    void drawButton(sf::Vector2f);
    int onClick(Packet::Lobbies&);
    int activateLobby(sf::Vector2f);
    int handleEvents(Packet::Lobbies&, sf::Event);

private:
    sf::RenderWindow& _Window;
    const int _WindowX;
    const int _WindowY;
    Textures _Text;
};
}

#endif /* !GAME_HPP */