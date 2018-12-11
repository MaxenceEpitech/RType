#ifndef MENU_HPP

#include "Textures.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace RType {

    class Menu {
    public:
        Menu(sf::RenderWindow &, const int, const int);

        ~Menu() = default;

        int handleEvents();

        int onClick();

        int menuLoop();

        void drawSprites();

        void movePlanet();
        //void setLauncher(const std::string &, const std::string &);
    private:
        sf::RenderWindow &_Window;
        const int _WindowX;
        const int _WindowY;
        sf::Clock _Clock;
        sf::Vector2f _PlanetPosition;
        double _Direction;
        const unsigned int _Frames;
        sf::Event _Event;
        Textures _Text;
        double startPos;
    };
} // namespace RType

#endif /* !MENU_HPP */