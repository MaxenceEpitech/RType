#include "EventHandler.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "UDPClient.hpp"
#include <array>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace RType {
class Core {
public:
    Core(std::vector<std::string>& argv, const int, const int,
        const std::string&);

    void setGame();
    void clientLoop(int);
    void initUDP();
    void interpretPacket(sf::Packet, int);
    void handleGraphicalPacket(sf::Packet, int);
    void joinMenu();
    void noLobbies();
    void displayLobbies(Packet::Lobbies);
    void gameLoop();

private:
    sf::Font _font;
    sf::Text _hud;
    bool _lost = false;
    std::vector<std::string>& argv;
    sf::RenderWindow _Window;
    const int _WindowX;
    const int _WindowY;
    const unsigned int _Frames;
    UDPClient* _Client;
    Game* _Game;
};

} // namespace RType
